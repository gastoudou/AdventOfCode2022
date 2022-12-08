The program is ready, let's write the first challenge.

https://adventofcode.com/2022/day/1

# 1 - Read the context
We have a data list, representing calories, 1 line = 1 calorie value.
We have a blank line to separate the elves inventories.

# 2 - Question
Find the Elf carrying the most Calories. How many total Calories is that Elf carrying?

# 3 - What to do
In this case, we have a list of inventories, and we need to sum each lines per elf.
Which means that we need to go through all data, and add each line to the previous ones, except if it is a blank line and in this case we will change to a new elf.
Then, we need to sort by value to know which elf has the highest value.

# 4 - How to do
This is a typical case of ***break*** algorithm.
We are looping of the input, add the value, and ***break*** if there's a change (blank line -> switch elf)

So in pseudo code:
```
initialise my current sum to 0
initialise my current elf id to 0
do
	read line
	if my line is blank
		add the sum to the elf
		change elf
	else
		add the value to my current sum
end
```

# 5 - Let's roll

First, we know already the answer to the puzzle given in the example
![[Pasted image 20221202110448.png]]

In this case, we will start with these inputs, and try to have a working algorithm before starting with the real inputs.

- create Day1.cpp file
- edit to add `#include "stdafx.h"`
- add `void Day1() { }` . This is the famous definition necessary to compile, after having a first extern declaration in main.cpp
- we need to add the inputs, let's just use a fixed array of string. We are using string in this case, because we will receive the real inputs as text soon.
![[Pasted image 20221202114117.png]]
- we will need to add the vector and string reference to the stdafx.h file first, as we will use them to store elves, or using the string library.
![[Pasted image 20221202113339.png]]
- now, we need to add a dynamic array (std::vector) to store for each elf (represented by the line in the array) the number of calories brought with `std::vector< uint32_t > calories_per_elf;`
- we should initialize everything first wit `uint32_t sum = 0u;`
- we can read the inputs, and start to loop, adding the read value to a sum. The value we are receiving is a text, so the function `atoi` will transform the text in integer (if valid of course)
```
	for ( size_t i = 0u; i < test_inputs.size(); ++i )
	{
		const std::string& line = test_inputs[ i ];
		if ( !line.empty() )
		{
			sum += static_cast< uint32_t >( atoi( line.c_str() ) );
		}
	}
```
- it's time to add the ***break*** in the algorithm. Each time we have a blank line (`line.empty() == true` ), we are incrementing the elf_id, adding the sum to the array, and resetting the sum.
```
calories_per_elf.push_back( sum );
sum = 0;
elf_id++;
```
- we need to find the highest calories value, so we will add a comparison each time we are adding a sum in the array to see if it's higher than the highest we have now. Before adding in the calories_per_elf array, add
```
if ( biggest_calories < sum )				
{
	biggest_calories = sum;
	biggestcalories_provider_elf_id = elf_id;
}
```
- one thing is still missing, is the ability to add everything at the end of the reading. The last line of the array is not triggering the blank line, so not triggering the last add, so we have some dangling sum. Just add it at the end of the loop. But, as one of rules of programming is DYI (Don't Repeat Yourself), we will use a lambda to make it and factorise the code.
```
auto set_sum = [ & ] ()
{
	if ( biggest_calories < sum )
	{
		biggest_calories = sum;
		biggestcalories_provider_elf_id = elf_id;
	}

	calories_per_elf.push_back( sum );
	sum = 0;
	elf_id++;
};
```
- last thing is to display on screen that we have calculated, to validate the algorithm.
![[Pasted image 20221202114841.png]]


The algorithm should look like that

![[Pasted image 20221202121308.png]]

Let's run it and see:
![[Pasted image 20221202121444.png]]
Sounds good!

Now, we need to change the inputs, to receive a file instead of the string array.
We are going to use some old-C library, easy to use.
Check documentation here: https://cplusplus.com/reference/cstdio/fopen/

First, we need to download the inputs, and put the file at the same level than the project.

![[Pasted image 20221202122159.png]]

And save the file here

![[Pasted image 20221202122406.png]]

The code is starting to be messy, let's refactor to have 3 functions, one to load, one to process, one to display.

![[Pasted image 20221202132452.png]]

![[Pasted image 20221202132504.png]]

`const std::vector< std::string > load_inputs()`
`void process( const std::vector< std::string >& inputs, data& data )`
`void display_result( data& data )`

And now, we are loading the real inputs

![[Pasted image 20221202132708.png]]

We are receiving ALL characters from the file, even the special characters. That's why we need to clear (remove the last one) before storing in the input array.

Let's compile and run it
![[Pasted image 20221202132859.png]]

So now, it's time to send it to see if it's working fine?

![[Pasted image 20221202132341.png]]

ALL GOOD!! Let's go to part 2.

# 6 - Part II

Using the same inputs, and same algorithm, we are extending it.
The idea is to find the best 3.

So, we are changing the calories_per_elf structure, to be able to sort it and save the IDs.
`std::vector< std::pair< uint32_t, uint32_t > > calories_per_elf;`

The add is also modified to be align with the new structure
`data.calories_per_elf.push_back( std::make_pair( data.elf_id, data.sum ) );`

We can now, at the end of the process just sort descending and retrieve the first 3.
![[Pasted image 20221202135525.png]]

Test with the test data is good.

![[Pasted image 20221202135559.png]]

Test with real data inputs
![[Pasted image 20221202135734.png]]

![[Pasted image 20221202135755.png]]

Let's go to day 2.

# 7 - Annex: Final Code Listing - part 1

```
#include "stdafx.h"

// #define TEST_DATA 1

struct data
{
	std::vector< uint32_t > calories_per_elf;

	uint32_t sum = 0u;
	uint32_t elf_id = 0u;
	uint32_t biggestcalories_provider_elf_id = 0u;
	uint32_t biggest_calories = 0u;
};

const std::vector< std::string > load_inputs()
{
#ifdef TEST_DATA
	const std::vector< std::string > test_inputs =
	{
		"1000",
		"2000",
		"3000",
		"",
		"4000",
		"",
		"5000",
		"6000",
		"",
		"7000",
		"8000",
		"9000",
		"",
		"10000"
	};
	return test_inputs;
#else
	std::vector< std::string > real_inputs;

	FILE* real_inputs_file;
	auto result = fopen_s( &real_inputs_file, "data/day1/input.txt", "r" );

	if ( result == 0 )
	{
		char buffer[ 128 ];
		char* read;
		while ( read = fgets( buffer, 128, real_inputs_file))
		{
			std::string line( read );
			line = line.substr( 0, line.size() - 1 ); // remove /n
			real_inputs.push_back( line );
		}
		fclose( real_inputs_file ); // ALWAYS CLOSE AN OPENED FILE
	}
	return real_inputs;
#endif
}

void process( const std::vector< std::string >& inputs, data& data )
{
	auto set_sum = [&] ()
	{
		if ( data.biggest_calories < data.sum )
		{
			data.biggest_calories = data.sum;
			data.biggestcalories_provider_elf_id = data.elf_id;
		}

		data.calories_per_elf.push_back( data.sum );
		data.sum = 0;
		data.elf_id++;
	};

	for ( size_t i = 0u; i < inputs.size(); ++i )
	{
		const std::string& line = inputs[ i ];
		if ( line.empty() )
		{
			set_sum();
		}
		else
		{
			data.sum += static_cast< uint32_t >( atoi( line.c_str() ) );
		}
	}
	set_sum();
}

void display_result( data& data )
{
	std::cout << "Verification:" << std::endl;
	std::cout << "Number of elves: " << data.elf_id << std::endl;
	for ( auto val : data.calories_per_elf )
	{
		std::cout << val << std::endl;
	}
	std::cout << "Biggest calories are: " << data.biggest_calories << " by: " << data.biggestcalories_provider_elf_id << std::endl;
}

void Day1()
{
	data data;

	process( load_inputs(), data );
	display_result( data );
}
```

# 8 - Annex: Final Code Listing - part 2
```
#include "stdafx.h"

// #define TEST_DATA 1

struct data
{
	std::vector< std::pair< uint32_t, uint32_t > > calories_per_elf;

	uint32_t sum = 0u;
	uint32_t elf_id = 0u;
	uint32_t biggestcalories_provider_elf_id = 0u;
	uint32_t biggest_calories = 0u;
};

const std::vector< std::string > load_inputs()
{
#ifdef TEST_DATA
	const std::vector< std::string > test_inputs =
	{
		"1000",
		"2000",
		"3000",
		"",
		"4000",
		"",
		"5000",
		"6000",
		"",
		"7000",
		"8000",
		"9000",
		"",
		"10000"
	};

	return test_inputs;
#else

	std::vector< std::string > real_inputs;

	FILE* real_inputs_file;
	auto result = fopen_s( &real_inputs_file, "data/day1/input.txt", "r" );

	if ( result == 0 )
	{
		char buffer[ 128 ];
		char* read;
		while ( read = fgets( buffer, 128, real_inputs_file))
		{
			std::string line( read );
			line = line.substr( 0, line.size() - 1 ); // remove /n
			real_inputs.push_back( line );
		}
		fclose( real_inputs_file ); // ALWAYS CLOSE AN OPENED FILE
	}

	return real_inputs;

#endif
}

void process( const std::vector< std::string >& inputs, data& data )
{
	auto set_sum = [&] ()
	{
		if ( data.biggest_calories < data.sum )
		{
			data.biggest_calories = data.sum;
			data.biggestcalories_provider_elf_id = data.elf_id;
		}

		data.calories_per_elf.push_back( std::make_pair( data.elf_id, data.sum ) );
		data.sum = 0;
		data.elf_id++;
	};

	for ( size_t i = 0u; i < inputs.size(); ++i )
	{
		const std::string& line = inputs[ i ];
		if ( line.empty() )
		{
			set_sum();
		}
		else
		{
			data.sum += static_cast< uint32_t >( atoi( line.c_str() ) );
		}
	}
	set_sum();

	std::sort( data.calories_per_elf.begin(), data.calories_per_elf.end(),
	[] ( const auto& left, const auto& right )
		{
			return left.second > right.second;
		}
	);
}

void display_result( data& data )
{
	std::cout << "Verification:" << std::endl;
	std::cout << "Number of elves: " << data.elf_id << std::endl;
	for ( auto val : data.calories_per_elf )
	{
		std::cout << "[" << val.first << "]" << val.second << std::endl;
	}
	std::cout << "Biggest calories are: " << data.biggest_calories << " by: "
	 << data.biggestcalories_provider_elf_id << std::endl;

	auto sum_best_3 = data.calories_per_elf[ 0 ].second
	 + data.calories_per_elf[ 1 ].second
	 + data.calories_per_elf[ 2 ].second;
	std::cout << "The best 3 are: " << std::endl;
	std::cout << data.calories_per_elf[ 0 ].first << std::endl;
	std::cout << data.calories_per_elf[ 1 ].first << std::endl;
	std::cout << data.calories_per_elf[ 2 ].first << std::endl;
	std::cout << "for a total of " << sum_best_3 << std::endl;
}

void Day1()
{
	data data;

	process( load_inputs(), data );
	display_result( data );
}
```
