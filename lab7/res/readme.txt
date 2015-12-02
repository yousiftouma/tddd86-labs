/**********************************************************************
 *  M�nsterigenk�nning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga k�rtider i sekunder
 *  analys      n�r det k�nns vettigt att v�nta p� hela ber�kningen.
 *              Ge uppskattningar av k�rtiden i �vriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150       51          37
    200       114         77
    300       332         661
    400       755         1390
    800       5801        5918
   1600       46243       24518
   3200       372043
   6400       3000000
  12800       24000000


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck f�r v�rstafallstiden f�r programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(n^4)

What the algorithm does is it goes through all groups of four points where the order matters, this is by definition n choose 4 groups which is n!/4!(n-4)! which we can simplify by disregarding constants to n*(n-1)*(n-2)*(n-3) = O(n^4)
This case will rarely happen as it requires the first three points to collinear, therefor the average case is closer to n^3 (the last iteration is skipped).

Sortering:
