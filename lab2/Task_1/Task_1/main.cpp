﻿#include "stdafx.h"
#include "Window.h"


int main(int, char *[])
{
	glewInit();

	CWindow window;
	window.Show({ 800, 600 });
	window.DoGameLoop();

	return 0;
}