
https://adventofcode.com/2022/day/3

# 1 - Part I

## a. Read the context

We receive a list of characters (items) and we need to check if they are duplicated.
Then, for those duplicates, sum their current code.

## b. Question

What is the sum of all duplicates per line?

## c. What to do

First, we need to be sure to get the correct code per character. As a character is actually an integer code, 'a' isn't really 'a' but `int value_a = 'a';`.
Then, we can just use the offset to compute the code of the character.

Second, we need to get the size of the line, split in two, and check if there's duplicates. We can probably assume that we will have a duplicate, and only one.
So we just need to loop on each character of the first part, try to find it in the second part, and if o, adding his code to the sum, and get to the next line.

## d. How to do

```
for each line do
	split the line in two parts of the same size
	for each character in the first part do
		if this character is found in the second part then
			add his code to the global sum
			stop
```

## e. Let's roll

As said earlier, first thing first is to be able to convert the code of the character to the correct value.
I would like to find some smart one line idea, but it's sounds like it's not going to happen.

if we prompt quickly some code values, we will realize that the value of 'A' is smaller than 'a'.

```
void display_result( data& data )
{
	std::cout << "value of a: " << int( 'a' ) << std::endl;
	std::cout << "value of z: " << int( 'z' ) << std::endl;
	std::cout << "value of A: " << int( 'A' ) << std::endl;
	std::cout << "value of Z: " << int( 'Z' ) << std::endl;
}
```

value of a: 97
value of z: 122
value of A: 65
value of Z: 90

The explanation of why 'A' is smaller than 'a' is that the byte used to switch from upper to lower case is set to 0 in the case of upper case and 1 to lower case (8th byte in the character integer).
You'll find all explanation in the book `Write Great Code: Understanding the Machine, Volume I by Randall Hyde`, chapter 5 `Character representation`.

We need to have 'A' bigger than 'a'. One way to do it is just to have a map of characters and their values.
```
std::map< char, int > look_up_char_code = 
{
	{ 'a', 1 },
	{ 'b', 2 },
	...
	{ 'Z', 52 }
};
```

Or, we can check if the character is between 'a' and 'z', substract 96 and return, or between 'A' and 'Z', substract 38 and return.
```
if ( current_char >= 'a' && current_char <= 'z' )
	return current_char - 96;
else if ( current_char >= 'A' && current_char <= 'Z' )
	return current_char - 38;
```

And we want to be fancy and use bitmask to check if the character is upper or lower, we can use the & operator, and compare to a shifted integer.
We know that the 5th byte is used for lower/upper case.
We create a mask with the byte 1 at 5th position and 0 for the others. In order to do that, we are taking 1 and "move" it to the 5th position.
`int mask = 1 << 5;` which gives us the binary `00010000`.
Makes the code like
```
if ( current_char & ( 1 << 5 ) )
	return current_char - 96;
else
	return current_char - 38;
```

Now we have the converting code, let's read the inputs, split and search.
This is not optimized at all, but brute force is working here.

```
for ( auto line : inputs )
{
	size_t half_size = line.size() / 2;
	for ( size_t i = 0u; i < half_size; ++i )
	{
		auto it_search = std::find( line.cbegin() + half_size, line.cend(), line[i]); // search in the second half
		if( it_search != line.cend() ) // we found something
		{
			data.score += convert( line[ i ] );
			break;
		}
	}
}
```

Validation with test data : 157. All good!

Let's try with real data now.

![day3_part1_star](https://user-images.githubusercontent.com/14072620/206675627-48881065-bdc4-4c28-acda-477b2b28e3c7.jpg)

# 2 - Part II

## a. Read the context

## b. Question

## c. What to do

## d. How to do

## e. Let's roll
