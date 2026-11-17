/* 파일 이름: server.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <systemd/sd-bus.h>

static int method_send(sd_bus_message *m, void *userdata, sd_bus_error *ret_error)
{
    const char *text;
    int r;

    r = sd_bus_message_read(m, "s", &text);
    if (r < 0) {
        fprintf(stderr, "읽기 실패: %s\n", strerror(-r));
        return r;
    }

    printf("[서버] 알림 받음: %s\n", text);
    return sd_bus_reply_method_return(m, "s", "알림을 받았습니다");
}

static const sd_bus_vtable vtable[] = {
    SD_BUS_VTABLE_START(0),
    SD_BUS_METHOD("Send", "s", "s", method_send, SD_BUS_VTABLE_UNPRIVILEGED),
    SD_BUS_VTABLE_END
};

int main(void)
{
    sd_bus *bus = NULL;
    sd_bus_slot *slot = NULL;
    int r;

    r = sd_bus_open_user(&bus);
    if (r < 0) {
        fprintf(stderr, "버스 연결 실패: %s\n", strerror(-r));
        return 1;
    }

    r = sd_bus_add_object_vtable(bus, &slot, "/com/example/Notify",
                                 "com.example.Notify", vtable, NULL);
    if (r < 0) {
        fprintf(stderr, "객체 등록 실패: %s\n", strerror(-r));
        return 1;
    }

    r = sd_bus_request_name(bus, "com.example.Notify", 0);
    if (r < 0) {
        fprintf(stderr, "이름 등록 실패: %s\n", strerror(-r));
        return 1;
    }

    printf("[서버] 알림을 기다리는 중...\n");

    while (1) {
        r = sd_bus_process(bus, NULL);
        if (r < 0)
            break;
        if (r > 0)
            continue;
        r = sd_bus_wait(bus, (uint64_t)-1);
        if (r < 0)
            break;
    }

    sd_bus_slot_unref(slot);
    sd_bus_unref(bus);
    return 0;
}
