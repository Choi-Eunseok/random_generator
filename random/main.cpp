#include <iostream>

// Finds e^x. x>0 or x<0 OK
double myExp(const double& x, const int& n)// e^x - no error finding
{
	double sum = 0.0;// retVal
	double a = 1.0;// 1st term

	if (n > 0)
		for (int j = 1; j <= n; j++)
		{
			sum += a;
			a *= x / (double)j;
		}

	return sum;
}// end of myExp() 

// Give x > 0.0 only
double myNatLog(const double& x, const int& n)// ln(x) - no error finding
{
	double   u = 1.0;// to substitute for x
	double   a = 0.0;// 
	double sum = 0.0;//

	if ((n > 0) && (x > 0.0))
	{
		if (x < 2.0)
		{
			u = 1 - x;// u will remain within interval of convergence ( u^2 < 1 )
			sum = a = u;// ist term
			for (int j = 2; j <= n; j++)//
			{
				a *= u;
				sum += a / (double)j;
			}
			return (-1.0 * sum);
		}
		else// x > 2.0
		{
			u = (x - 1) / x;// u will remain within interval of convergence ( u^2 < 1 )
			sum = a = u;// ist term
			for (int j = 2; j <= n; j++)
			{
				a *= u;
				sum += a / (double)j;
			}
			return (sum);
		}
	}

	return 0.0;// How to handle bad input?
}// end of myNatLog() 

// Finds base^x. Must input base >0 . This works best for "smallish" base and exponent (<10 or so).
double myPow(const double& base, const double& x, const int& n)// base^x - no error finding
{
	double u = 1.0;
	if ((base > 0.0) && (n > 0))
	{
		u = x * myNatLog(base, n);
		return (myExp(u, n));
	}
	else
		return 0.0;// error
}// end of myPow() 

int pseudo_uniform(int size)
{
	int mult = 16807;
	int mod = 2147483647;
	static int x = 123456789; // seed
	x = (x * mult + 1) % mod;
	int random = (double)x / (double)mod * size/2 + size / 2;
	return random;
}

double pseudo_uniform(double flag)
{
	int mult = 16807;
	int mod = 2147483647;
	static int x = 123456789; // seed
	x = (x * mult + 1) % mod;
	double random = (double)x / (double)mod * 0.5 + 0.5;
	return random;
}

int pseudo_bernoulli(int size)
{
	double result;
	double u = pseudo_uniform(0.1);
	result = myNatLog(u / (1.0 - u), 100) / myNatLog(10,100);
	return ((int)(result * size / 4 + size / 2) + size * 10) % size;
}

#define SIZE 10
#define COUNT 10000

int main()
{
	int test_uniform_arr[SIZE] = { 0 };
	for (int i = 0; i < COUNT; i++)
	{
		int temp = pseudo_uniform(SIZE);
		test_uniform_arr[temp]++;
		//std::cout << temp << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < SIZE; i++)
	{
		std::cout << test_uniform_arr[i] << ' ';
	}
	std::cout << "  <= 균등한 확률을 가지는 난수 생성 " << std::endl;
	int test_logistic_arr[SIZE] = { 0 };
	for (int i = 0; i < COUNT; i++)
	{
		int temp = pseudo_bernoulli(SIZE);
		test_logistic_arr[temp]++;
		//std::cout << temp << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < SIZE; i++)
	{
		std::cout << test_logistic_arr[i] << ' ';
	}
	std::cout << "  <= 로지스틱 분포를 따르는 난수 생성 " << std::endl;


	return 0;
}