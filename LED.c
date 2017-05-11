




int main()
{
int count = 0;
int countLEDA = 0;
int countLEDB = 0;
	for(;;)
	{
		delay(5ms);//assume all other operations are infinitely fast.
		count++;
		if(count%50 == 0)
		{	
			//turn on LEDA
		}
		if(LEDA)
		{
			countLEDA++;
		}
		if(countLEDA == 25)
		{
			countLEDA = 0;
			//turn off LEDA
		}
		if(count%66 == 0)
		{
			//turn on LEDB
		}
		if (LEDB)
		{
			countLEDB++;
		}
		if(countLEDB == 20)
		{
			countLEDB = 0;
			//turn off LEDB
		}
	}

	return 0;
}

//It would be trivial to change the program to turn the LEDs on at different
//intervals for different tims becuase you just change the if statements