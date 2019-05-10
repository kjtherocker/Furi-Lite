#ifndef __PlayerController_H__
#define __PlayerController_H__

enum PlayerControllerButtons
{
    PCB_Mouse = 0x00000010,
	PCB_MouseR = 0x00000020,
    PCB_Up    = 0x00000001,
    PCB_Down  = 0x00000002,
    PCB_Left  = 0x00000004,
    PCB_Right = 0x00000008,
};

class PlayerController
{
protected:
    unsigned int m_ButtonFlags;

public:
    PlayerController();
    virtual ~PlayerController();

    void Clear();

    void SetButtonPressed(PlayerControllerButtons button);
    void SetButtonReleased(PlayerControllerButtons button);

    bool IsButtonPressed(PlayerControllerButtons button);
    bool IsButtonReleased(PlayerControllerButtons button);

    void OnEvent(Event* pEvent);
};

#endif //__PlayerController_H__
