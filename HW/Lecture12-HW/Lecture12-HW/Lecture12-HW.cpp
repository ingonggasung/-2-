#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main()
{
	//start	
	int count = 0;
	int prev_dur_ms = 0;
	int sleep = 0;

	chrono::steady_clock::time_point prev_end = chrono::steady_clock::now();
	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	while (count < 10)
	{
		/*prev_end = end;
		end = chrono::steady_clock::now();
		count++;

		cout << count ;
		end = chrono::steady_clock::now();
		this_thread::sleep_for(chrono::milliseconds(1000));
		chrono::steady_clock::duration dur = end - prev_end;
		int duration_ms = chrono::duration_cast<chrono::milliseconds>(dur).count();
		int sleep = 1000 - duration_ms;
		this_thread::sleep_for(chrono::milliseconds(sleep));
		cout << "\tduration_ms" << duration_ms << endl;*/
		/*if (duration_ms>1000)
		{
			break;
		}*/
		prev_end = end;
		end = chrono::steady_clock::now();
		count++;
		chrono::steady_clock::duration diff = end - prev_end;
		int duration_ms = chrono::duration_cast<chrono::milliseconds>(diff).count();
		cout << count << "\t\t1000 - duration_ms : " << 1000 - duration_ms << endl;
		int sleep = 1000 - duration_ms;
		if (sleep < 0)
		{
			this_thread::sleep_for(chrono::milliseconds(1000 - sleep));
		}
		else this_thread::sleep_for(chrono::milliseconds(sleep));

		////정답
		////슬립
		//this_thread::sleep_for(chrono::milliseconds(1000 + delay_time_ms));
		////시작시간과 끝시간
		//prev_end = end;
		//end = chrono::steady_clock::now();
		////시간차 구하기
		//chrono::steady_clock::duration diff = end - prev_end;
		//delay_time_ms = 1000 - chrono::duration_cast<chrono::milliseconds>(diff).count();
		////출력
		//count++;
		//cout << count << "   dur:" << delay_time_ms << endl;
	}
}
//prev_end = end;
		//end = chrono::steady_clock::now();
		//count++;
		//
		//cout << count << endl;
		//end = chrono::steady_clock::now();
		//this_thread::sleep_for(chrono::milliseconds(1000));
		//chrono::steady_clock::duration dur = end - start;
		//int duration_ms = chrono::duration_cast<chrono::milliseconds>(dur).count();
		//if (duration_ms>1000)
		//{
		//	break;
		//}