#include <iostream>

using namespace std;

void Print()
{
	cout << "Hello World" << endl;
}

int Add(int a, int b)
{
	return a + b;
}



using FuncPtrType = int(*)(int a, int b);

int DoSomething(int a, int b, FuncPtrType func)
{
	return func(a, b);
}

class Item
{
public:

public:
	int _itemId = 0;
	int _rarity = 0;
	int _ownerId = 0;
};

using ItemSelectorType = bool(*)(Item* item);

Item* FindItem(Item items[], int itemCount, ItemSelectorType selector)
{
	for (int i = 0; i < itemCount; i++)
	{
		Item* item = &items[i];
		if (item->_rarity == 1)
			return item;
	}

	return nullptr;
}

bool IsRare(Item* item)
{
	return item->_rarity == 1;
}


// 함수 객체 예제
class Functor 
{
public:
	
	void operator()()
	{
		cout << "Functor Test" << endl;
		cout << _value << endl;
	}

	void operator()(int n)
	{
		cout << "Functor Test" << endl;
		_value += n;
		cout << _value << endl;
	}

public:
	int _value = 0;
};




struct AddStruct
{
public:
	int operator()(int a, int b)
	{
		return a + b;
	}
};

template<typename T>
int DoSometingByTemplate(int a, int b, T func)
{
	return func(a, b);
}

class Job
{
public :

	Job() { }
	// 최상위 클래스에 가상 함수를 붙이지 않으면
	// 자식 소멸자가 실행이 안될 가능성이 매우 높기 때문에
	// 꼭, 꼭 virtual 해줘야한다.
	virtual ~Job() { }		
};

class MoveJob : public Job
{
public:
	MoveJob(int x, int y) : x(x), y(y) {}

	void operator()()
	{
		cout << "player move" << endl;
	}

public:
	int x;
	int y;
};

class AttackJob : public Job
{

};

int main()
{
	// 함수 포인터
	// 행동 자체를 인자로 넘기고 싶을 때 사용

	// 사용 예제 : 콜백 함수
	// - ex) UI
	// - ex) 온라인 게임
	// - ex) 키보드 입력

	//typedef void FuncType();
	//using FuncType = void();
	//FuncType* ptr = &Print;

	//void(*FuncPtrType)();
	using FuncType = void(*)();
	FuncType funcPtr = &Print;
	funcPtr();


	DoSomething(10, 20, &Add);
	// 익명함수 활용
	DoSomething(10, 20, [](int a, int b) {return a - b; });

	// 조건별로 함수 실행시
	Item items[10];
	items[3]._rarity = 1; // RARE
	FindItem(items, 10, IsRare);

	// 함수 포인터는 행동은 인자로 넘길수 있지만 동적으로 데이터랑 묶어서 실행이 어렵다.
	// 이를 해결하기 위해서 함수 객체를 사용한다.

	// 함수 객체
	// 함수 포인터의 단점
	// - 시그니처가 안 맞으면 사용 X
	// - 상태를 가질 수 없음


	AddStruct func;
	//DoSomething(10, 20, func);		// 함수 포인터를 지정해놔서 이렇게는 못 쓴다.
	DoSometingByTemplate(10, 20, func);

	// mmo 에서 활용되는 경우
	// 클라 : (10, 20) 좌표로 이동할래?
	MoveJob* job = new MoveJob(10, 20);

	// 공격 해줄래?
	AttackJob* attackJob = new AttackJob();

	// ...

	(*job)();

	// 이러한 다양한 잡들을 다형성과 큐라는 자료구조를 이용해 관리하면 순서도 보장되기 때문에 멀티스레드 환경에서 매우 좋다.
	// queue<Job*>
	// 연결리스트로도 관리할 수 있다. 연결리스트로는 중간에 잡이 취소되면 장점이 있다.
}
