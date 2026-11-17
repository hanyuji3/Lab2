/* 파일 이름: client.c */
#include <stdio.h>
#include <stdlib.h>
#include <systemd/sd-bus.h>

int main(int argc, char *argv[])
{
    sd_bus *bus = NULL;
    sd_bus_error error = SD_BUS_ERROR_NULL;
    sd_bus_message *reply = NULL;
    const char *answer;
    int r;

    if (argc != 2) {
        printf("사용법: %s \"알림 내용\"\n", argv[0]);
        return 1;
    }

    r = sd_bus_open_user(&bus);
    if (r < 0) {
        fprintf(stderr, "버스 연결 실패\n");
        return 1;
    }

    r = sd_bus_call_method(bus, "com.example.Notify", "/com/example/Notify",
                           "com.example.Notify", "Send",
                           &error, &reply, "s", argv[1]);
    if (r < 0) {
        fprintf(stderr, "호출 실패: %s\n", error.message);
    } else {
        sd_bus_message_read(reply, "s", &answer);
        printf("[클라이언트] 서버 응답: %s\n", answer);
    }

    sd_bus_error_free(&error);
    sd_bus_message_unref(reply);
    sd_bus_unref(bus);
    return 0;
}
