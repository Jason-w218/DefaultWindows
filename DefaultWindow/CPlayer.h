#pragma once
#include "CObj.h"
class CPlayer :
    public CObj
{
public:
    enum STATE { IDLE, WALK, ATTACK, HIT, DEATH, END };

public:
    CPlayer();
    virtual ~CPlayer();

public:   
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    void    Key_Input();
    void    Jumping();
    void    Offset();
    void    Motion_Change();

    template<typename T>
    CObj* Create_Bullet(float fX, float fY, float fAngle);

    CObj* Create_Shield();

private:
    POINT               m_tPosin;    
    bool                m_bJump;

    float               m_fVelocity;
    float               m_fTime;

    STATE               m_eCurState;
    STATE               m_ePreState;

};

