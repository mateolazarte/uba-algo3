# GERGOVIA - Wine trading in Gergovia

## Description
Gergovia consists of one street, and every inhabitant of the city is a wine salesman. Everyone buys wine from other inhabitants of the city. Every day each inhabitant decides how much wine he wants to buy or sell. Interestingly, demand and supply is always the same, so that each inhabitant gets what he wants.

There is one problem, however: Transporting wine from one house to another results in work. Since all wines are equally good, the inhabitants of Gergovia don't care which persons they are doing trade with, they are only interested in selling or buying a specific amount of wine.

In this problem you are asked to reconstruct the trading during one day in Gergovia. For simplicity we will assume that the houses are built along a straight line with equal distance between adjacent houses. Transporting one bottle of wine from one house to an adjacent house results in one unit of work.

## Input
The input consists of multiple test cases. 

Each test case starts with the number of inhabitants $N$ $ (2 \le n \le 100,000) $. 

The next line contains $n$ integers $a_i$  $( -1000 \le a_i \le 1000 )$

If $a_i$ ≥ 0, it means that the inhabitant living in the i-th house wants to buy ai bottles of wine. If $a_i$ < 0, he wants to sell -$a_i$ bottles of wine.

You may assume that the numbers $a_i$ sum up to 0.

The last test case is followed by a line containing 0.

## Output
For each test case print the minimum amount of work units needed so that every inhabitant has his demand fulfilled.

## Example

### Input
5<br>
5 -4 1 -3 1<br>
6<br>
-1000 -1000 -1000 1000 1000 1000<br>
0

### Output
9<br>
9000