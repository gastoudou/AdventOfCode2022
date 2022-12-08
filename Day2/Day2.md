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

and adding the score

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

## b. Question

## c. What to do

## d. How to do

## e. Let's roll
