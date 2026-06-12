// ============================================================
// Name    : Aden Nguyen
// Course  : COSC 1437 — Programming Fundamentals II
// Date    : 06/09/2026
// Program : Chapter 4 Major Project
// Option  : Hotel Billing
// Purpose : Calculates hotel group-discounts based on 
//           number of rooms reserved, length 
//           of stay, and prints a billing receipt.
// ============================================================

// ----------  SECTION: PSUEDOCODE DESIGN BLOCK  ----------
/*

    Get roomRate     // assume > 0
    Get numRooms     // assume > 0
    Get numNights    // assume > 0 
    Get taxRate      // assume > 0
    
    

    IF numRooms >= 30
        apply 30% discount
        discountTier = 3
    ELSE IF numRooms >= 20
        apply 20% discount
        discountTier = 2
    ELSE IF numRooms >= 10
        apply 10% discount
        discountTier = 1
    ELSE 
        apply no discount
        discountTier = 0
    END IF

    discountedRate = roomRate * (1 - discountPercent)
    IF numNights >= 3 AND  numRooms >=10
        apply loyalty discount
    ELSE
        dont apply loyalty discount
    END IF
    
    subTotal = discountedRate * numRooms * numNights
    taxAmount = subTotal * (taxRate/100);
    totalBill = subTotal + taxAmount;

    switch(discountTier)
         case 0:
            print("Tier 0: 0% Discount: Fewer than 10 rooms") 
            break
         case 1:
           print("Tier 1: 10% Discount: 10 Rooms or more") 
           break
         case 2:
           print("Tier 2: 20% Discount: 20 Rooms or more") 
           break
         case 3:
           print("Tier 3: 30% Discount: 30 Rooms or more") 
           break
        default:
           print("ERROR") 
           break
    end switch      
*/

#include <iostream>
#include <iomanip>     
#include <string>    
#include <cassert>  
#include <cmath>
 
using namespace std;
 
int main()
{   
    constexpr double DISCOUNT_TIER1 = .10; //(10% off)
    constexpr double DISCOUNT_TIER2 = .20; //(20% off)
    constexpr double DISCOUNT_TIER3 = .30; //(30% off) 
    constexpr double LOYALTY_DISCOUNT = .05; //(5% off)

    constexpr int MIN_ROOMS_TIER1 = 10;
    constexpr int MIN_ROOMS_TIER2 = 20;
    constexpr int MIN_ROOMS_TIER3 = 30;
    constexpr double EPSILON = 0.0001; 
    

    constexpr int MIN_NIGHTS_LOYALTY = 3;
   


    double roomRate, taxRate;
    int numRooms, numNights;

    // ----------  SECTION: INPUT VALIDATION  ----------
    cout << "Enter the nightly rate per room >> ";
    cin >> roomRate;
    assert(roomRate > 0.0); //Invarient: Room rate must be positive, program aborts if assert is fired
    cout << "Enter the number of rooms >> ";
    cin >> numRooms;
    assert(numRooms > 0); //Invarient: At least one room must be booked, program aborts if assert is fired
    cout << "Enter the number of nights >> ";
    cin >> numNights;
    assert(numNights > 0); //Invarient: Stay length must be positive, program aborts if assert is fired
    cout << "Enter the tax rate >> ";
    cin >> taxRate;
    assert(taxRate >= 0.0); //Invarient: Tax Rate must be greater than 0, program aborts if assert is fired

    /* ----------  SECTION: Operator Precedence Reference  ----------
    
        Precedence          Operator(s)         Category            Associativity
        1 (highest)         !                   Logical NOT         Right-to-Left
        2                   *,/,%               Multiplicative      Left-to-right
        3                   +,-                 Additive            Left-to-Right
        4                   <,<=,>,>=           Relational          Left-to-Right
        5                   ==,!=               Equality            Left-to-Right
        6                   &&                  Logical AND         Left-to-Right
        7(lowest)           ||                  Logical OR          Left-to-Right

        !(rooms > 0) || (rate >= 50.0 && rooms != nights)
        rooms = 5
        rate = 75
        nights = 4

        !(5 > 0) || (75 >= 50.0 && 5 != 4) 
        1. FALSE || (75 >= 50.0 && 5 != 4) 
        2. FALSE || TRUE && 5!=4
        3. FALSE || TRUE && TRUE
        4. FALSE || TRUE
        5. TRUE
    */

    // ----------  SECTION: Core Logic  ----------

    int discountTier = 0;
    double roomDiscountPercent;

    if (numRooms >= MIN_ROOMS_TIER3) // relational operator >=
    {
        roomDiscountPercent = DISCOUNT_TIER3;
        discountTier = 3;
    }
    else if (numRooms  >= MIN_ROOMS_TIER2)
    {
        roomDiscountPercent = DISCOUNT_TIER2;
        discountTier = 2;
    }
    else if(numRooms  >= MIN_ROOMS_TIER1)
    {
       roomDiscountPercent = DISCOUNT_TIER1;
        discountTier = 1;
    }
    else
    {
       roomDiscountPercent = 0.0;
        discountTier = 0;
    }
    double discountedRate = roomRate * (1.0 - roomDiscountPercent);
    if((numRooms >= MIN_ROOMS_TIER1) && (numNights >= MIN_NIGHTS_LOYALTY)) // relational operator && 
    {
        discountedRate *= (1.0 - LOYALTY_DISCOUNT);
    }
    double subTotal = discountedRate * numRooms * numNights;
    double taxAmount = subTotal * (taxRate/100);
    double totalBill = subTotal + taxAmount;

    
 // ----------  SECTION: Switch Statement ----------

    switch(discountTier)
    {
         case 0:
            cout << "Tier 0: No discount: Customer booked fewer than 10 rooms" << endl;
            break;
         case 1:
            cout << "Tier 1: 10% discount: Customer booked atleast 10 rooms" << endl;
           break;
         case 2:
           cout << "Tier 2: 20% discount: Customer booked atleast 20 rooms" << endl;
           break;
         case 3:
          cout << "Tier 3: 30% discount: Customer booked atleast 30 rooms" << endl;
           break;
        default:
          cout << "ERROR: Unexpected discount tier";
           break;
    }
  
    
// ----------  SECTION:  Relational & Logical Operator Showcase ----------
    cout << "Relational & Logical Operator Showcase " << endl;

    if (numRooms > MIN_ROOMS_TIER3) 
        cout << "Operator > demonstrated" << endl;
    
    if (numRooms <  MIN_ROOMS_TIER1) 
        cout << "Operator < demonstrated" << endl;
        
    if (discountTier != 0)
        cout << "Operator != demonstrated" << endl;
    
    if (discountTier == 0)
         cout << "Operator == demonstrated" << endl;
    if (numRooms <= MIN_ROOMS_TIER1)
         cout << "Operator <= demonstrated" << endl;
    if (!(numNights < 1))
        cout << "Operator ! demonstrated" << endl;
    if (numRooms >= MIN_ROOMS_TIER3 || numNights >= MIN_NIGHTS_LOYALTY)
         cout << "Operator || demonstrated" << endl;






/*----------  SECTION:  Floating-Point Bug Guard ----------
    Comparing floating-point values with == is unrealiable because deciamal values are often
    sorted with small rounding errors.

    Instead of 
    value == otherValue

    fabs(value-otherValue) < EPSILON

    EPSILON = 0.0001
    This tolerance is small enough for currency calculations while avoiding
    mismatches caused by floating-point rounding.


*/ 
if (fabs(roomDiscountPercent - DISCOUNT_TIER1) < EPSILON) 
    { 
        cout << "Discount is effectively 10%." << endl; 
    }


// ----------  SECTION:  Formatted Output / Receipt ----------
cout << "========================================================" << endl;
cout << "HOTEL RECEIPT" << endl;
cout << "========================================================" << endl;

cout << fixed << setprecision(2);

cout << left << setw(30) << "Nightly Rate:"
     << right << "$" << setw(12) << roomRate << endl;

cout << left << setw(30) << "Discount Percent:"
     << right << setw(12) << roomDiscountPercent * 100 << "%" << endl;

cout << left << setw(30) << "Rooms:"
     << right << setw(13) << numRooms << endl;

cout << left << setw(30) << "Number of Nights:"
     << right << setw(13) << numNights << endl;

cout << left << setw(30) << "Total before Tax:"
     << right << "$" << setw(12) << subTotal << endl;

cout << left << setw(30) << "Sales Tax Amount:"
     << right << "$" << setw(12) << taxAmount  << endl;

cout << left << setw(30) << "Total after Tax:"
     << right << "$" << setw(12) << totalBill << endl;

/* ----------  SECTION:   Known Bug Risks ----------

Missing break in switch
Risk:
Fall-through could print multiple tier messages.
Prevention:
Every case includes a break statement.

Incorrect discount tier ordering
Risk:
Checking 10-room tier before 30-room tier would prevent
larger discounts from being applied.
Prevention:
Conditions are evaluated from highest discount to lowest.

Dangling else
Risk:
An else could attach to the wrong if statement.
Prevention:
Consistent braces are used for every conditional block.
*/
    
return 0;
}
/* Test Run #1
    Enter the nightly rate per room >> 101
    Enter the number of rooms >> 42
    Enter the number of nights >> 4
    Enter the tax rate >> 8.5
    Tier 3: 30% discount: Customer booked atleast 30 rooms
    Relational & Logical Operator Showcase 
    Operator > demonstrated
    Operator != demonstrated
    Operator ! demonstrated
    Operator || demonstrated
    ========================================================
    HOTEL RECEIPT
    ========================================================
    Nightly Rate:                 $      101.00
    Discount Percent:                    30.00%
    Rooms:                                   42
    Number of Nights:                         4
    Total before Tax:             $    11283.72
    Sales Tax Amount:             $      959.12
    Total after Tax:              $    12242.84
*/

/* Test Run #2
    Enter the nightly rate per room >> 100
    Enter the number of rooms >> 5
    Enter the number of nights >> 3
    Enter the tax rate >> 0
    Tier 0: No discount: Customer booked fewer than 10 rooms
    Relational & Logical Operator Showcase 
    Operator < demonstrated
    Operator == demonstrated
    Operator <= demonstrated
    Operator ! demonstrated
    Operator || demonstrated
    ========================================================
    HOTEL RECEIPT
    ========================================================
    Nightly Rate:                 $      100.00
    Discount Percent:                     0.00%
    Rooms:                                    5
    Number of Nights:                         3
    Total before Tax:             $     1500.00
    Sales Tax Amount:             $        0.00
    Total after Tax:              $     1500.00
*/
