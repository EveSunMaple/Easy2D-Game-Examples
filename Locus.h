#pragma once
#include <easy2d/easy2d.h>

using namespace easy2d;

auto locus = new ShapeNode;
void trejectory()
{
    DrawingStyle style;
    style.mode = DrawingStyle::Mode::Solid; // ��ͼģʽΪ���
    style.fillColor = Color::White;           // ���ɫ
    locus = ShapeNode::createCircle(10, style);
    auto scaleto = new ScaleTo(1, 0.1f);
    auto opacityTo = new OpacityTo(1.2f, 0.0f);
    auto two = new Spawn({ scaleto, opacityTo });
    locus->setAnchor(0.5f, 0.5f);
    locus->runAction(two);
}