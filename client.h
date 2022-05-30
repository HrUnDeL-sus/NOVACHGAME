#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED
enum ClientAction {
            RenderingWorld,
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown,
        MoveForward,
        MoveBack,
        SetBlock,
		RotateLeft,
		RotateRight,
		GetCameraPosition,
		Jump
    };
int client_UID;
int connect_to_server();
void send_state(int state);
#endif // CLIENT_H_INCLUDED
