//
//  main.cpp
//  MTH9815_HW2
//
//  Created by 王明森 on 11/28/22.
//

#include <iostream>
#include "products.hpp"
#include "productservice.hpp"

using namespace std;

void TestProducts() {
    // Create the 10Y treasury note
    date maturityDate(2025, Nov, 16);
    string cusip = "912828M56";
    Bond treasuryBond(cusip, CUSIP, "T", 2.25, maturityDate);

    // Create the 2Y treasury note
    date maturityDate2(2017, Nov, 5);
    string cusip2 = "912828TW0";
    Bond treasuryBond2(cusip2, CUSIP, "T", 0.75, maturityDate2);

    // Create a BondProductService
    BondProductService *bondProductService = new BondProductService();

    // Add the 10Y note to the BondProductService and retrieve it from the service
    bondProductService->Add(treasuryBond);
    Bond bond = bondProductService->GetData(cusip);
    cout << "CUSIP: " << bond.GetProductId() << " ==> " << bond << endl;

    // Add the 2Y note to the BondProductService and retrieve it from the service
    bondProductService->Add(treasuryBond2);
    bond = bondProductService->GetData(cusip2);
    cout << "CUSIP: " << bond.GetProductId() << " ==> " << bond << endl;

    delete bondProductService;
    
    // Create the Spot 10Y Outright Swap
    date effectiveDate(2015, Nov, 16);
    date terminationDate(2025, Nov, 16);
    string outright10Y = "Spot-Outright-10Y";
    IRSwap outright10YSwap(outright10Y, THIRTY_THREE_SIXTY, THIRTY_THREE_SIXTY, SEMI_ANNUAL, LIBOR, TENOR_3M, effectiveDate, terminationDate, USD, 10, SPOT, OUTRIGHT);

    // Create the IMM 2Y Outright Swap
    date effectiveDate2(2015, Dec, 20);
    date terminationDate2(2017, Dec, 20);
    string imm2Y = "IMM-Outright-2Y";
    IRSwap imm2YSwap(imm2Y, THIRTY_THREE_SIXTY, THIRTY_THREE_SIXTY, SEMI_ANNUAL, LIBOR, TENOR_3M, effectiveDate2, terminationDate2, USD, 2, IMM, OUTRIGHT);

    // Create a IRSwapProductService
    IRSwapProductService *swapProductService = new IRSwapProductService();

    // Add the Spot 10Y Outright Swap to the IRSwapProductService and retrieve it from the service
    swapProductService->Add(outright10YSwap);
    IRSwap swap = swapProductService->GetData(outright10Y);
    cout << "Swap: " << swap.GetProductId() << " ==> " << swap << endl;

    // Add the IMM 2Y Outright Swap to the IRSwapProductService and retrieve it from the service
    swapProductService->Add(imm2YSwap);
    swap = swapProductService->GetData(imm2Y);
    cout << "Swap: " << swap.GetProductId() << " ==> " << swap << endl;
    
    delete swapProductService;
}

void TestFuture() {
    // Create a 1Y corn future
    date corn_maturityDate(2023, Dec, 1);
    string corn_id("ZCZ3");
    Future corn_future(corn_id, "Corn", 1000, 660, corn_maturityDate);
    
    // Create the 10Y treasury note and a bond future with the bond as the underlying asset.
    date bond_maturityDate(2032, Nov, 15);
    string cusip = "91282CFV8";
    Bond treasuryBond(cusip, CUSIP, "T", 2.25, bond_maturityDate);
    
    string bond_future_id("ZNH3");
    date bond_future_maturity(2023, Mar, 1);
    BondFuture bond_future(bond_future_id, &treasuryBond, 10, 114.215, bond_future_maturity);
    
    // Create a 2Y eurodollar future
    date eurodollar_maturityDate(2023, Dec, 1);
    string eurodollar_future_id("GEZ3");
    EuroDollarFuture eurodollar_future(eurodollar_future_id, 100, 96., eurodollar_maturityDate);

    // Create a BondProductService
    FutureProductService *futureProductService = new FutureProductService();

    // Add the corn future to the BondProductService and retrieve it from the service
    futureProductService->Add(corn_future);
    Future retrieved_corn_future = futureProductService->GetData(corn_id);
    cout << "Future ID: " << retrieved_corn_future.GetProductId() << " ==> " << retrieved_corn_future << endl;

    // Add the bond future to the BondProductService and retrieve it from the service
    futureProductService->Add(bond_future);
    Future retrieved_bond_future = futureProductService->GetData(bond_future_id);
    cout << "Future ID: " << retrieved_bond_future.GetProductId() << " ==> " << retrieved_bond_future << endl;

    
    // Add the corn future to the BondProductService and retrieve it from the service
    futureProductService->Add(eurodollar_future);
    Future retrieved_eurodollar_future = futureProductService->GetData(eurodollar_future_id);
    cout << "Future ID: " << retrieved_eurodollar_future.GetProductId() << " ==> " << retrieved_eurodollar_future << endl;

}

int main() {
//    TestProducts();
    
    TestFuture();
    
    return 0;
}
