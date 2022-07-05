#include "t_machine.h"

t_machine::t_machine(TBufferedWindow* wnd) {
	this->wnd = wnd;
	auto buf = wnd->GetBuffer();
	buf->ClearAllLayers();
	for (int layer = 0; layer < buf->LayerCount; layer++) {
		for (int y = 0; y < buf->Rows; y++) {
			for (int x = 0; x < buf->Cols; x++) {
				buf->GetTile(layer, x, y).Add(0, 0, 0);
			}
		}
	}
}
t_machine::~t_machine() {
}
