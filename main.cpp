#include <string>
#include <thread>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <functional>

const bool StartsWith(
	const std::string& p_Text,
	const std::string& p_Pattern)
{
	bool l_result(true);

	if ( p_Text.length() >= p_Pattern.length() )
	{				
		for (unsigned int i(0);
			i < p_Pattern.length();
			++i)
		{
			if ( p_Text[i] != p_Pattern[i] )
			{
				l_result = false;
				break;
			}
		}
	}
	else
	{
		l_result = false;
	}

	return l_result;
}

const bool AltStartsWith(
	const std::string& p_Text,
	const std::string& p_Pattern)
{	
	return (p_Text.find(p_Pattern) == 0);
}

int main ()
{
	std::string l_Source ("Mary Had a Little Lamb, Its Fleece was White as Snow");
	std::string l_Positive ("Mary");
	std::string l_PositiveLong ("Mary Had a Little Lamb, Its Fleece was White as Sno");
	std::string l_Negitive ("Alfred");

	auto l_altfunction(
		[](
			const std::string& p_Name,
			const std::string& p_Source,
			const std::string& p_Pattern,
			const unsigned long& p_Max)
		{
			auto l_Start(
				std::chrono::high_resolution_clock::now());
			unsigned long l_Count(0);
			while ( l_Count < p_Max )
			{
				AltStartsWith(p_Source, p_Pattern);
				++l_Count;
			}
			auto l_End(
				std::chrono::high_resolution_clock::now());				
			std::cout << "Test '" << p_Name << ": ";
			std::cout << std::chrono::duration_cast<std::chrono::microseconds>(l_End - l_Start).count() << std::endl;
		});

	auto l_function (
		[](
			const std::string& p_Name,
			const std::string& p_Source,
			const std::string& p_Pattern,
			const unsigned long& p_Max)
		{
			auto l_Start(
				std::chrono::high_resolution_clock::now());
			unsigned long l_Count(0);
			while ( l_Count < p_Max )
			{
				StartsWith(p_Source, p_Pattern);
				++l_Count;
			}
			auto l_End(
				std::chrono::high_resolution_clock::now());				
			std::cout << "Test '" << p_Name << ": ";
			std::cout << std::chrono::duration_cast<std::chrono::microseconds>(l_End - l_Start).count() << std::endl;
		});

	auto l_ShortTest(
		std::bind(		
			l_function,
			"Short",
			l_Source,
			l_Positive,
			500000));
	auto l_LongTest(
		std::bind(			
			l_function,
			"Long",
			l_Source,
			l_PositiveLong,
			500000));	
	auto l_NegativeTest(
		std::bind(			
			l_function,
			"Negative",
			l_Source,
			l_Negitive,
			500000));

	auto l_AltShortTest(
		std::bind(		
			l_altfunction,
			"Alt Short",
			l_Source,
			l_Positive,
			500000));
	auto l_AltLongTest(
		std::bind(			
			l_altfunction,
			"Alt Long",
			l_Source,
			l_PositiveLong,
			500000));	
	auto l_AltNegativeTest(
		std::bind(			
			l_altfunction,
			"Alt Negative",
			l_Source,
			l_Negitive,
			500000));

	std::thread l_t1 (l_ShortTest);
	std::thread l_t2 (l_LongTest);
	std::thread l_t3 (l_NegativeTest);

	l_t1.join();
	l_t2.join();
	l_t3.join();

	l_t1 = std::thread(l_AltShortTest);
	l_t2 = std::thread(l_AltLongTest);
	l_t3 = std::thread(l_AltNegativeTest);

	l_t1.join();
	l_t2.join();
	l_t3.join();
}