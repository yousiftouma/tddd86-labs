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
    150       51          17
    200       114         48
    300       332         89
    400       755         143
    800       5801        579
   1600       46243       1831
   3200       372043	  5664	
   6400       3000000	  22153
  12800       24000000


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(n^4)

What the algorithm does is it goes through all groups of four points where the order matters, this is by definition n choose 4 groups which is n!/4!(n-4)! which we can simplify by disregarding constants to n*(n-1)*(n-2)*(n-3) = O(n^4)
This case will rarely happen as it requires the first three points to collinear, therefor the average case is closer to n^3 (the last iteration is skipped).

Sortering:
