/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150       0.051        0.017
    200       0.114        0.048
    300       0.332        0.089
    400       0.755        0.143
    800       5.801        0.579
   1600       46.243       1.831
   3200       372.043	   5.664	
   6400       3000.000	   22.153
  12800       24000.000    105.965


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(n^4)

What the algorithm does is it goes through all groups of four points where the order matters, this is by definition n choose 4 groups which is n!/4!(n-4)! which we can simplify by disregarding constants to n*(n-1)*(n-2)*(n-3) = O(n^4)
This case will rarely happen as it requires the first three points to collinear, therefor the average case is closer to n^3 (the last iteration is skipped).

Sortering: O(n² log n)
The improved algorithm goes through allmost every point (n-3) and sorts the remaining points (n log n) using quicksort, then it processes the sorted points one by one. This results in the (n-3)((n-4) log (n-4) + (n-4) operations which is the same as O(n² log n).
