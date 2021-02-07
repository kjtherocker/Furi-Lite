#include "GamePCH.h"

CameraObject::CameraObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale)
: GameObject( pScene, name, pos, rot, scale, 0, 0, 0)
{
    m_pPlayerObject = 0;
}

CameraObject::~CameraObject()
{
}

void CameraObject::Update(float deltatime)
{
   

    if (m_pPlayerObject == nullptr)
    {
        m_MatView.SetIdentity();
        m_MatView.Translate(m_Position * -1);


        m_MatProj.CreatePerspectiveVFoV(45, 600.0f / 600.0f, 0.01f, 100);

    m_Rotation.y = 90;

    //m_Rotation.y = 90;
    }
    if (m_pPlayerObject != nullptr)
    {
        float cx = ((float)cos(m_Rotation.x / 180 * PI));
        float sx = ((float)sin(m_Rotation.x / 180 * PI));
        float cy = ((float)cos(m_Rotation.y / 180 * PI));
        float sy = ((float)sin(m_Rotation.y / 180 * PI));

        float distance = 20;
        vec3 eye = vec3(-distance*cx*sy, distance*sx, -distance*cx*cy);
        vec3 playerpos = m_pPlayerObject->GetPosition();
        eye += playerpos;

        m_Position = eye;
    
        m_MatView.CreateLookAtViewLeftHanded(eye, vec3(0, 1, 0), m_Rotation);

       /* m_MatView.SetIdentity();
        m_MatView.Translate(m_Position * -1);*/

       

        //
       // m_MatView.CreateLookAtViewLeftHanded(eye, vec3(0, 1, 0), m_Rotation);

        

        m_MatProj.CreatePerspectiveVFoV(45, 600.0f / 600.0f, 0.01f, 100);
    }


    GameObject::Update( deltatime );
}

vec4 CameraObject::GetTrueMouseCoord(vec2 mousecoord)
{
    float windowheight = float(m_pScene->GetGame()->GetWindowHeight());
    float windowWidth = float(m_pScene->GetGame()->GetWindowWidth());

    vec4 mousecoords = vec4(mousecoord.x, mousecoord.y, 0, 1);
    float y = windowheight - mousecoord.y;

    float x = mousecoords.x / (windowWidth / 2.0f) - 1.0f;
    y = y / (windowheight / 2.0f) - 1.0f;

    vec4 screenpos = vec4(x, y, 0, 1);

    mat4 inverseVP = m_MatProj * m_MatView;
    inverseVP.Inverse();

    vec4 worldpos = inverseVP * screenpos;

    vec3 worldspacepoint = vec3(worldpos.x, worldpos.y, worldpos.z) / worldpos.w;

    vec3 Direction = worldspacepoint - m_Position;

    float N = float((0.0f - m_Position.z) / Direction.z);

    vec4 FinalPos = vec4(m_Position + Direction * N, 0);

    worldpos.x *= 10 / 0.4f;
    worldpos.y *= 10 / 0.4f;

    return vec4(FinalPos);
}
