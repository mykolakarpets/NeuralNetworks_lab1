#include "TPerceptron.h"



TPerceptron::TPerceptron()
{
	order = DEF_DIMENTION;
	w = new double[order];
	for (int i = 0; i < order; i++)
		w[i] = 0;
	b = 0;
}

TPerceptron::TPerceptron(int order)
{
	srand(time(0));
	this->order = order;
	w = new double[order];
	for (int i = 0; i < order; i++)
	{
		//srand(time(0));
		double f = (double)rand() / RAND_MAX;
		w[i] = RAND_BOT_B + f * (RAND_UP_B - RAND_BOT_B);
	}
	//srand(time(0));
	double f = (double)rand() / RAND_MAX;
	b = /*0;*/ RAND_BOT_B + f * (RAND_UP_B - RAND_BOT_B);
}

TPerceptron::TPerceptron(double * w, double b, int order)
{
	w = new double[order];
	for (int i = 0; i < order; i++)
		this->w[i] = w[i];
	this->order = order;
	this->b = b;
}

TPerceptron::TPerceptron(TPerceptron & p)
{
	order = p.order;
	w = new double[order];
	for (int i = 0; i < order; i++)
		this->w[i] = p.w[i];
	b = p.b;
}

TPerceptron & TPerceptron::setW(double * w)
{
	for (int i = 0; i < order; i++)
		this->w[i] = w[i];
	return *this;
}

TPerceptron & TPerceptron::setB(double b)
{
	this->b = b;
	return *this;
}

int TPerceptron::signFunc(double * x)
{
	double sum = 0;
	for (int i = 0; i < order; i++)
		sum += w[i] * x[i];
	sum -= b;
	return (sum > 0 ? 1 : -1);
}

int * TPerceptron::signFunc(double ** x, int count)
{
	int * result = new int[count];
	for (int i = 0; i < count; i++)
		result[i] = signFunc(x[i]);
	return result;
}

char * TPerceptron::print()
{
	char * result = new char[5000];
	strcpy(result, "");
	char * buff = new char[256];
	for (int i = 0; i < order; i++)
	{
		
		strcpy(buff,"");
		sprintf(buff, "%1.7f", w[i]);
		strcat(result,buff);
		strcat(result, "\t");
		
	}
	strcpy(buff, "");
	sprintf(buff, "%1.7f", b);
	strcat(result, buff);
	delete[] buff;

	return result;
}

double * TPerceptron::studWithTeacher(double ** x, int * answers, int count, double k)
{
	double * result = new double[order];
	bool isContinue = true;

	while (isContinue)
	{
		//random pair from preset
		int numOfAns = rand() % count;

		//result with current weight vector
		int curRes = signFunc(x[numOfAns]);

		//modifying w vector if result incorrect
		int delta = answers[numOfAns] - curRes;
		if (delta != 0)
		{
			for (int i = 0; i < order; i++)
				this->w[i] += k*(delta)*(x[numOfAns][i]);
			this->b -= k*delta;
		}	
		
		int * newRes = signFunc(x, count);
		isContinue = !(arrCompare(newRes,answers,count));
		delete[] newRes;
	}

	for (int i = 0; i < order; i++)
		result[i] = w[i];

	return result;
}

bool TPerceptron::arrCompare(int * a, int * b, int count)
{
	bool result = true;
	for (int i = 0; i < count; i++)
	{
		cout << a[i] << "\t" << b[i] << endl;
		if (a[i] != b[i]) result = false;
	}
	return result;
}


TPerceptron::~TPerceptron()
{
	delete[] w;
	w = NULL;
	b = 0;
	order = 0;
}
