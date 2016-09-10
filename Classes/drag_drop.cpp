#include "PCH.h"
#include "drag_drop.h"
usings

static Vec2 lastPos;

void drag_drop_end(EventListenerMouse* listener, Event* _)
{
	listener->onMouseMove = nullptr;
	listener->onMouseUp = nullptr;
}

void drag_drop_move(DragDropHandler handler, Event* event)
{
	auto e = (EventMouse&)*event;
	auto currentPos = e.getLocation();

	handler(
		currentPos.x - lastPos.x,
		currentPos.y - lastPos.y
	);

	lastPos = currentPos;
}

void drag_drop_start(EventListenerMouse* listener, DragDropHandler handler, int btn, Event* event)
{
	auto e = (EventMouse&)*event;

	if (e.getMouseButton() == btn)
	{
		lastPos = e.getLocation();
		listener->onMouseMove = bind(drag_drop_move, handler, _1);
		listener->onMouseUp   = bind(drag_drop_end, listener, _1);
	}
}

void on_drag_drop(Node* node, DragDropHandler handler, int btn)
{
	auto listener = EventListenerMouse::create();

	listener->onMouseDown = bind(drag_drop_start, listener, handler, btn, _1);

	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}