#pragma once
#include <PESP/Prerequisites.h>
#include <PESP/Entity/Component.h>
#include <PESP/Math/Vector4d.h>

class FogComponent : public Component
{
public:
    FogComponent();
    virtual ~FogComponent();

    void setData(const Vector4D& color, f32 start, f32 end);

    Vector4D getColor();
    f32 getStart();
    f32 getEnd();
protected:
    virtual void onCreateInternal();
private:
    Vector4D m_color = Vector4D(0.5f, 0.5f, 0.5f, 1.0f);
    f32 m_start = 50;
    f32 m_end = 300;
private:
    friend class GraphicsEngine;
};