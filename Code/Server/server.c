/*
 * server.c
 *
 *  Created on: AUG 04, 2022
 *      Author: Nabil Gamal
 */


#define _CRT_SECURE_NO_WARNINGS 1

#include	"Server.h"
#include	<stdio.h>



#include	<string.h>

#define DataBase_Max_SIZE 255

uint32 flag_check = 0;
uint32 sequence = 1;

/*Data base for the card info {Balance, PAN, Name/ID}*/
ST_accountsDB_t Arr_accountsDB_t[DataBase_Max_SIZE] =
{
    {1000,  "1234 5678 9101 1121","Ahmed Khaled Mohammed"},
    {900,   "3141 5161 7181 9202","Mohammed Esmail Elsayed",},
    {300,   "1222 3242 5262 7282","Essam Mostafa Atyaa"},
    {50,    "9303 1323 3343 5363","Mohamed Abdelshafy Ayman"}
};

/*Blocked and stolen cards data base*/
ST_accountsDB_t Arr_StolenAccountsDB_t[DataBase_Max_SIZE] =
{
    {35000,  "1478 5202 3669 9874","Elsayed Mostafa Hussain"},
    {9000,   "1014 7852 3214 5698","Bayoumi Mohamed Khaled",},
};


ST_transaction_t Arr_transactionsDB_t[DataBase_Max_SIZE];


/*function to clear the parameters*/
void ST_Fill_Zero(ST_transaction_t* transactionDB, uint32 size)
{
    uint32 i = 0;

    for (i = 0; i < size; i++)
    {
        strcpy(transactionDB[i].cardHolderData.cardExpirationDate,       "0");
        strcpy(transactionDB[i].cardHolderData.cardHolderName,           "0");
        strcpy(transactionDB[i].cardHolderData.primaryAccountNumber,     "0");

        strcpy(transactionDB[i].terminalData.transactionDate,            "0");
        transactionDB[i].terminalData.maxTransAmount                                     = 0;
        transactionDB[i].terminalData.transAmount                                        = 0;

        transactionDB[i].transactionSequenceNumber                                       = 0;
        transactionDB[i].transState                                                      = 0;
    }

}

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
    uint32  isValidCard;
    uint32  isAvailableAmount;
    uint32  isTransactionSaved;
    uint32  GetMaxAmount;
  //  uint8   isValidTransDate;

  //  isValidTransDate = getTransactionDate(&(transData->terminalData));

  //  
  //  isValidTransDate = isValidDATE(&(transData->terminalData));

    
    isValidCard         = isValidAccount(&(transData->cardHolderData));
    

    GetMaxAmount        = setMaxAmount(&(transData->terminalData));

    isAvailableAmount   = isAmountAvailable(&(transData->terminalData));

    /*checks if the card is stolen -> wrong ID - Date and if the card has low balance*/
    if (isCardExpired(transData->cardHolderData, transData->terminalData) == EXPIRED_CARD)
    {
        printf("Your Card Is Expired\n");
        return DECLINED_STOLEN_CARD;
    }

    if (isValidCard == ACCOUNT_NOT_FOUND)
    {
        transData->transState = DECLINED_STOLEN_CARD;


    }

    else if (isAvailableAmount == LOW_BALANCE)
    {

        transData->transState = DECLINED_INSUFFECIENT_FUND;

    }

    else
    {

        transData->transState = APPROVED;

    }

    /*start saving the card info*/
    transData->transactionSequenceNumber = sequence;

    isTransactionSaved = saveTransaction(transData);



    if ((isValidCard == ACCOUNT_NOT_FOUND) )
    {
        printf("Stolen Card\n");

        return DECLINED_STOLEN_CARD;
    }

    /*checks if the card is valid or not and if so, print succeeded and finsh the withdraw process and decrease the balance*/
    else if ((isValidCard == OK_SER) && (flag_check != 255))
    {
        if (isAvailableAmount == LOW_BALANCE)
        {
            printf("Low balance\n");
            return DECLINED_INSUFFECIENT_FUND;
        }

        else if (isTransactionSaved == SAVING_FAILED)
        {
            printf("Internal Server Error\n");
            return INTERNAL_SERVER_ERROR;
        }

        else if ((isBelowMaxAmount(&(transData->terminalData)) == OK_TER) && (isValidCard == OK_CARD))
        {
            //ARR_ST_accountDB[flag_check].balance = ARR_ST_accountDB[flag_check].balance - transData->terminalData.transAmount;
            Arr_accountsDB_t[flag_check].balance -= transData->terminalData.transAmount;
            printf("Succeeded\n");
           
        }

    }

    return APPROVED;

    

}


EN_terminalError_t isValidDATE(ST_terminalData_t* termData)
{
    uint8   isValidTransDate;
    //uint32  flag = 0;
    isValidTransDate = getTransactionDate(termData);
    
    /*loop until the the user writes a valid date*/
    while (isValidTransDate == WRONG_DATE)
    {
        isValidTransDate = getTransactionDate(&(termData->transactionDate));
        //printf("%d\n", isValidTransDate);
    }

}

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
    uint8   isValidName;
    uint8   isValidExDate;
    uint8   isValidPrimaryAccountNumber;
    uint8   isTransactionSaved;
   
    int flag = 0;

    isValidName = getCardHolderName(cardData);

    /*loop until the the user writes a valid Name - ex date - pan*/
    while (isValidName == WRONG_NAME)
    {
        isValidName = getCardHolderName(cardData);
    }

    isValidExDate = getCardExpiryDate(cardData);

    while (isValidExDate == WRONG_EXP_DATE)
    {
        isValidExDate = getCardExpiryDate(cardData);
    }


    isValidPrimaryAccountNumber = getCardPAN(cardData);

    while (isValidPrimaryAccountNumber == WRONG_PAN)
    {
        isValidPrimaryAccountNumber = getCardPAN(cardData);
       // isTransactionSaved = saveTransaction(cardData);

    }

    /*condition to check if the card details if right and valid*/
    if ((isValidName == OK_CARD) && (isValidPrimaryAccountNumber == OK_CARD) && (isValidExDate == OK_CARD))
    {
        
        
        uint32 i = 0;
        for (i = 0; i < DataBase_Max_SIZE; i++)
        {
            //flag = 0;
           /*strcpy(Arr_accountsDB_t[i].primaryAccountNumber, cardData->primaryAccountNumber);
            strcpy(Arr_accountsDB_t[i].uint32CardNameHolder, cardData->cardHolderName);*/
            //printf("%d\n", i);

            if ((strcmp(cardData->primaryAccountNumber, Arr_accountsDB_t[i].primaryAccountNumber) == 0))
            {
                
                /*flag = 3;
                printf("%d\n", flag);*/
                if ((strcmp(cardData->cardHolderName, Arr_accountsDB_t[i].uint32CardNameHolder) == 0))
                {
                    /*flag = 2;
                    printf("%d\n", flag);*/
                    flag_check = i;
                    return OK_SER;
                }

                
                
            }

            else if ((strcmp(cardData->primaryAccountNumber, Arr_StolenAccountsDB_t[i].primaryAccountNumber) == 0))
            {
                if ((strcmp(cardData->cardHolderName, Arr_StolenAccountsDB_t[i].uint32CardNameHolder) == 0))
                {
                   
                    /*flag = 1;
                    printf("%d\n", flag);*/ 
                    return ACCOUNT_NOT_FOUND;
                }

                
            }
           // return OK_SER;
        }
        /*flag++;
        printf("%d\n", flag);*/
        flag_check = DataBase_Max_SIZE;
    }
    /*flag = 4;
    printf("%d\n", flag);*/
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
    uint8 isAmountAvailable;

    isAmountAvailable = getTransactionAmount(termData);

    if (isAmountAvailable == OK_TER)
    {
        if (termData->transAmount > Arr_accountsDB_t[flag_check].balance)
        {
            return LOW_BALANCE;
        }

        return OK_SER;
    }
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
    uint32 i = sequence - 1;
    
    if (i >= 255)
    {
        return SAVING_FAILED;
    }

    strcpy(Arr_transactionsDB_t[i].cardHolderData.cardExpirationDate, transData->cardHolderData.cardExpirationDate);
    strcpy(Arr_transactionsDB_t[i].cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName);
    strcpy(Arr_transactionsDB_t[i].cardHolderData.primaryAccountNumber, transData->cardHolderData.primaryAccountNumber);

    strcpy(Arr_transactionsDB_t[i].terminalData.transactionDate, transData->terminalData.transactionDate);

    Arr_transactionsDB_t[i].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
    Arr_transactionsDB_t[i].terminalData.transAmount = transData->terminalData.transAmount;

    Arr_transactionsDB_t[i].transactionSequenceNumber = transData->transactionSequenceNumber;
    Arr_transactionsDB_t[i].transState = transData->transState;



    sequence++;

    return OK_SER;

}

EN_serverError_t getTransaction(uint32 transactionSequenceNumber, ST_transaction_t* transData)
{
    uint32 GetTransBuffer = 0;
    while (transData[GetTransBuffer].transactionSequenceNumber != 0)
    {
        if (transData[GetTransBuffer].transactionSequenceNumber == transactionSequenceNumber)
        {
            printf("\n\nYour Transaction details:");



            printf("Your Card Holder Name - ID                    :\t%s\n", transData[GetTransBuffer].cardHolderData.cardHolderName);

            printf("Your Card Primary Account Number              :\t%s\n", transData[GetTransBuffer].cardHolderData.primaryAccountNumber);
            
            printf("The Card Expiry Date                          :\t%s\n", transData[GetTransBuffer].cardHolderData.cardExpirationDate);
            
            printf("Your Transaction Date                         :\t%s\n", transData[GetTransBuffer].terminalData.transactionDate);
            
            printf("The Transaction Amount                        :\t%f\n", transData[GetTransBuffer].terminalData.transAmount);
            
            printf("The Max Amount Your Can Transact              :\t%f\n", transData[GetTransBuffer].terminalData.maxTransAmount);

            printf("The Transaction Sequence Number               :\t%d\n", transData[GetTransBuffer].transactionSequenceNumber);
           
            printf("The Transaction State                         :\t%d\n", transData[GetTransBuffer].transState);



            return OK_SER;
        }
        GetTransBuffer++;
    }

    //puts("Transaction Not Found\n");
    printf("Transaction Not Found\n");
    return TRANSACTION_NOT_FOUND;
}