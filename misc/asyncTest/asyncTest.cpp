// asyncTest.cpp : Defines the entry point for the console application.
//



#include <future>
#include <iostream>

void called_from_async()
{
  std::cout << "Async call" << std::endl;
}

/***********************************
call async function with no variable
*************************************/
int main1()
{
	//called_from_async launched in a separate thread if possible
	std::future<void> result(std::async(called_from_async));

	std::cout << "Message from main." << std::endl;

	//ensure that called_from_async is launched synchronously
	//if it wasn't already launched
	result.get();

	getchar();
	return 0;
}

/***********************************
call async function with lambda
*************************************/
int main() 
{
	//called_from_async launched in a separate thread if possible
	std::future<int> result(std::async([](int m, int n) { return m + n; }, 2, 4));

	std::cout << "Message from main." << std::endl;

	//retrive and print the value stored in the future
	std::cout << result.get() << std::endl;
	getchar();
	return 0;
}