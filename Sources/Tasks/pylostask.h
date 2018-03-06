#ifndef PYLOSTASK_H
#define PYLOSTASK_H

#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Lights/Light.h"
#include "GraphicsEngine/Lights/LightDirectional.h"
#include "GraphicsEngine/Lights/LightSpot.h"
#include "GraphicsEngine/Lights/LightPoint.h"

#include "GraphicsEngine/Materials/MaterialTask01.h"
#include "GraphicsEngine/Materials/MaterialUnlit.h"
#include "GraphicsEngine/Materials/MaterialDiffuse.h"
#include "GraphicsEngine/Materials/MaterialDiffuseSpecular.h"
#include "GraphicsEngine/Materials/MaterialDiffuseAttenuation.h"

#include "GraphicsEngine/Meshes/MeshTriangle.h"
#include "GraphicsEngine/Meshes/MeshQuad.h"
#include "GraphicsEngine/Meshes/MeshSphere.h"
#include "GraphicsEngine/Meshes/MeshCube.h"
#include "GraphicsEngine/Meshes/MeshCylinder.h"

#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/Transform.h"
#include "Tasks/Task.h"
#include "Tasks/ObjectRotator.h"

#include "CameraController.h"


class PylosTask: public Task
{
public:
    virtual ~PylosTask() { }

    virtual void Init()
    {
        Scene & scene = Application::Instance().GetScene();

        // Камера
        {
            Object * pCameraObj = new Object();
            pCameraObj->m_pTransform = new Transform( Vector3(0.0f, 0.0f,-20), Vector3(0, 0, 0));
            Camera * pCamera = new Camera();
            pCameraObj->AddComponent( pCamera );
            pCameraObj->AddComponent(new CameraController());

            scene.SetCamera( pCamera );
        }


    }

    virtual void Update()
    {
       // if (Input::GetKey(KEY_CODE_A))
    }
};


#endif // PYLOSTASK_H
