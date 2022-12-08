The program is ready, let's write the first challenge.

https://adventofcode.com/2022/day/1

# 1 - Part I

## a. Read the context

We have a data list, representing calories, 1 line = 1 calorie value.
We have a blank line to separate the elves inventories.

## b. Question

Find the Elf carrying the most Calories. How many total Calories is that Elf carrying?

## c. What to do

In this case, we have a list of inventories, and we need to sum each lines per elf.
Which means that we need to go through all data, and add each line to the previous ones, except if it is a blank line and in this case we will change to a new elf.
Then, we need to sort by value to know which elf has the highest value.

## d. How to do

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

## e. Let's roll


First, we know already the answer to the puzzle given in the example

![Pasted image 20221202110448](https://user-images.githubusercontent.com/14072620/206482855-58ca46a3-a43b-4c7b-9b57-7f5826952ea7.png)

In this case, we will start with these inputs, and try to have a working algorithm before starting with the real inputs.

- create Day1.cpp file
- edit to add `#include "stdafx.h"`
- add `void Day1() { }` . This is the famous definition necessary to compile, after having a first extern declaration in main.cpp
- we need to add the inputs, let's just use a fixed array of string. We are using string in this case, because we will receive the real inputs as text soon.
![Pasted image 20221202114117](https://user-images.githubusercontent.com/14072620/206482957-fb69784b-381a-44ca-8591-d61acede7351.png)
- we will need to add the vector and string reference to the stdafx.h file first, as we will use them to store elves, or using the string library.
![Pasted image 20221202113339](https://user-images.githubusercontent.com/14072620/206483014-170a5d59-596e-4a4d-82ac-29d6dc64c696.png)
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
![Pasted image 20221202114841](https://user-images.githubusercontent.com/14072620/206483064-7f000540-3c81-4133-b154-59ef7fcc5573.png)

The algorithm should look like that
![Pasted image 20221202121308](https://user-images.githubusercontent.com/14072620/206483100-341460e5-32f8-4f0c-9026-e0ed761981f1.png)

Let's run it and see
![Pasted image 20221202121444](https://user-images.githubusercontent.com/14072620/206483139-924fbd2e-7294-46a6-a5ab-738a283f905e.png)

Sounds good!

Now, we need to change the inputs, to receive a file instead of the string array.
We are going to use some old-C library, easy to use.
Check documentation here: https://cplusplus.com/reference/cstdio/fopen/

First, we need to download the inputs, and put the file at the same level than the project.

![Pasted image 20221202122159](https://user-images.githubusercontent.com/14072620/206483196-6f577603-a13a-4294-b953-607053d1a894.png)


And save the file here

![Pasted image 20221202122406](https://user-images.githubusercontent.com/14072620/206483218-3ecdc3c7-2fb7-4b99-a74d-86bb5a3c162b.png)


The code is starting to be messy, let's refactor to have 3 functions, one to load, one to process, one to display.

![Pasted image 20221202132452](https://user-images.githubusercontent.com/14072620/206483237-bdc26cef-bea7-416e-9341-d24e674c8bbf.png)

![Pasted image 20221202132504](https://user-images.githubusercontent.com/14072620/206483255-d799e508-325b-48ca-bb21-8f90fac5ba0c.png)

`const std::vector< std::string > load_inputs()`
`void process( const std::vector< std::string >& inputs, data& data )`
`void display_result( data& data )`

And now, we are loading the real inputs

![Pasted image 20221202132708](https://user-images.githubusercontent.com/14072620/206483289-3d12463e-81ea-405f-b703-4215d6827c41.png)

We are receiving ALL characters from the file, even the special characters. That's why we need to clear (remove the last one) before storing in the input array.

Let's compile and run it

![Pasted image 20221202132859](https://user-images.githubusercontent.com/14072620/206483326-1f512e9f-47ad-4bbe-bceb-cb567ebf90ac.png)

So now, it's time to send it to see if it's working fine?

![Pasted image 20221202132341](https://user-images.githubusercontent.com/14072620/206483470-b7488988-631c-4250-8344-735633b23637.png)

ALL GOOD!! Let's go to part 2.

# 2 - Part II

## a. Read the context

Using the same inputs, and same algorithm, we are extending it.
The idea is to find the best 3.

## b. Question

What are the best 3 elves carrying calories?

## c. What to do

In the same algorithm, we are modifying the structure saving the calories to be able to sort per calories value and save the elf ID.
Then, we will return the first 3.

## d. How to do

```
< part I >

sort the array
retrieve the first 3
```

## e. Let's roll

So, we are changing the calories_per_elf structure, to be able to sort it and save the IDs.
`std::vector< std::pair< uint32_t, uint32_t > > calories_per_elf;`

The add is also modified to be align with the new structure
`data.calories_per_elf.push_back( std::make_pair( data.elf_id, data.sum ) );`

We can now, at the end of the process just sort descending and retrieve the first 3.
![Pasted image 20221202135525](https://user-images.githubusercontent.com/14072620/206483515-75959fc5-19f5-4e84-93b1-7c2ecec8f908.png)

Test with the test data is good.

![Pasted image 20221202135559](https://user-images.githubusercontent.com/14072620/206483535-5eb9a548-2a50-422e-afaf-c6f86a71620e.png)

Test with real data inputs

![Pasted image 20221202135734](https://user-images.githubusercontent.com/14072620/206483582-eee0456b-a865-479e-bf1d-b88a07f8939a.png)

![Pasted image 20221202135755](https://user-images.githubusercontent.com/14072620/206483601-22f6b5a9-82db-446f-91f4-2d828543ba21.png)

Let's go to day 2.
