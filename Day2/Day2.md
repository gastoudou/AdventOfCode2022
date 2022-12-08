Time for the next day.

https://adventofcode.com/2022/day/2

# 1 - Part I

First of all, we clean a bit the code, and prepare the code with using a namespace in each file, to separate "properly" the code.

![image](https://user-images.githubusercontent.com/14072620/206487243-f84bb12f-a3a3-488b-824f-c3d7e98ff896.png)

## a. Read the context

The data list represents the list of fights made, according to plan, in a string line.

## b. Question

Calculate the global score resulting of each fight.
Each fight result is and addition of the chosen shape, and the outcome.

## c. What to do

We will check each line, calculate the outcome, adding the shape value, and sum up to the score.

## d. How to do

Read the inputs, loop, and add. Pretty straigh forward.

```
read the inputs
for all inputs
	score += outcome + shape
```

## e. Let's roll

First, prepare the data to use.
We need to store the different shapes and their values.

![image](https://user-images.githubusercontent.com/14072620/206487874-56d89989-cb72-43cb-a3f7-a3e06160db48.png)

And now, we can probably store the outcomes values.
Actually, after consideration, the outcomes are not that numbered, and can be reduced to 6. And all these values can be already pre-calculated.
Let's remove the shapes_map and add a result_map

![image](https://user-images.githubusercontent.com/14072620/206488862-a041ee58-0e91-4afe-ad8f-d38e268147b8.png)

We are using a map here because there's not a lot of cases, and it's pretty easy to request the second element from the key (the first element).
The key is the `std::string` element ("A Y"), and the value is the score with this key (8 for "A Y").

We can summarize the map like that

![image](https://user-images.githubusercontent.com/14072620/206511791-b13ffc57-bcc3-438f-93a0-9cdae03e4d44.png)

Internally, the map is a [red-black tree](https://www.geeksforgeeks.org/introduction-to-red-black-tree/).

then, adding the score

![image](https://user-images.githubusercontent.com/14072620/206488993-00e8d708-f394-42d2-8b37-468446a81f20.png)

The inputs are simple, like the previous day.

![image](https://user-images.githubusercontent.com/14072620/206489251-8a48c324-1123-46c4-a6b2-5407eeded6bf.png)

Now, let's process them.

We need to read each line, get the outcome + shape value, and add it to the score. Without forgetting to initialize the score first.

![image](https://user-images.githubusercontent.com/14072620/206489588-e3eea2be-ccde-42a3-b686-4ac96126f3e1.png)

Displa the result is an easy step

![image](https://user-images.githubusercontent.com/14072620/206489761-dab1ef2b-eb9f-4193-9775-bb9f26b81ee0.png)

And test it.

![image](https://user-images.githubusercontent.com/14072620/206489944-0ddee329-38f5-480d-8392-0dc7bcfdb26f.png)

Sounds good, so now, let's use the real data.
Save the input.txt file in the data/day2/ folder and let's run it.

![image](https://user-images.githubusercontent.com/14072620/206490415-1faefe86-e54a-49bc-bcd4-6c2b288558d5.png)

Awesome! Move move to part II.

# 2 - Part II

## a. Read the context

So now, instead of naively reading the inputs and use the score, we need to choose the correct shape to fit the second character and calculate the score.
The algorithm for first part is going to be used, but with a slight twist.

## b. Question

What is the score if you need to follow the outcome already in the input?

## c. What to do

We are going to use the same algorithm, but change just the calculation.
We are going to use another table to get the choice we are making during the fight, as X, Y and Z are now the desired outcomes, creating this new combination, and get the score resulting of this combination.

## d. How to do

- Change the results_map to work with A/B/C vs A/B/C combination.
- Add a new map to return the new choice regarding the outcome needed defined in the input line.
- And get the score.

## e. Let's roll

The score calculation is changing with the shapes (we could already calculate the score directly, but let's add small step to be clear).

Change the results_map as

![image](https://user-images.githubusercontent.com/14072620/206503209-0bff0bb3-4f67-402b-bc4a-38131a047ede.png)

Then, add the new map, with the all possible cases, and the necessary choice to make.

![image](https://user-images.githubusercontent.com/14072620/206503712-c13de436-c9f8-4175-8b79-4834a0d2f145.png)

So this table we get us the choice we should make, and the results_map will get us the ... result ...

And now the loop in the the inputs looks like that
1 - we are requestion from the map the choice to make, as a key the input received.
2 - we are creating a new `std::string` with the correct choices made. We need to use `push_back()` function, as the `std::string` is actually a `std::vector` of `char`.

![image](https://user-images.githubusercontent.com/14072620/206504556-7511dd24-f1da-4164-a011-b74bb824d86b.png)

Test the algo

![image](https://user-images.githubusercontent.com/14072620/206508730-45614c0c-cf80-41fd-a1d0-2ec6c908464c.png)

Great!
Now, as we already have all real data, we just need to comment the `#define TEST_DATA 1` line and run it.

![image](https://user-images.githubusercontent.com/14072620/206509353-6010da89-f0b3-426e-b8f1-6b4ad38c685d.png)

Let's verify

![image](https://user-images.githubusercontent.com/14072620/206509590-55e7eba7-c0c1-471a-8161-4a56f7a70559.png)

Hup hup! All good!
