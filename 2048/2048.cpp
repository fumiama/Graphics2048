// 2048.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "ui.h"

int main() {
#undef UNICODE
#undef _UNICODE
	char flag = 1;
	while (flag) {
		initui();
		switch (menu()) {
		case 1:
			gamedisplay();
			listenprepare(listenplay);	
			while (havempty()) {
				if(!ISWIN && !ISFAIL) newblock();
				drawblocks();
				printmyscore();
				if (operate()) break;
			}
			listendestroy();	
			break;
		case 2:
			onlineinit();
			initgraph(640, 640);
			gamedisplay();
			listenprepare(listenplay);
			while (havempty()) {
				if (!ISWIN && !ISFAIL) newblock();
				drawblocks();
				print2score();
				if (operate()) break;
			}
			listendestroy();	
			break;
		case 3:
			loadimage(NULL, L"IMG", L"MAN", 640, 640);
			while (_getch() != 0x1B);
			break;
		case 4:
			closegraph();
			flag = 0;
			break;
		}
	}
	closegraph();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
