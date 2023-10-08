package main

import (
	"github.com/shopspring/decimal"
	"math/rand"
	"sync"
)

type BankAccount struct {
	balance decimal.Decimal
	mutex   sync.Mutex
}

// Transfer removes an amount of money from accountFrom and adds it accountTo if enough money is in accountFrom
func Transfer(accountFrom *BankAccount, accountTo *BankAccount, amount decimal.Decimal) bool {
	// locks are acquired on accountFrom first and accountTo after that. This requires that the caller always passes
	// arguments in specific order, otherwise a deadlock may occur here
	accountFrom.mutex.Lock()
	accountTo.mutex.Lock()
	defer accountFrom.mutex.Unlock()
	defer accountTo.mutex.Unlock()
	if amount.GreaterThan(accountFrom.balance) {
		return false
	}
	accountFrom.balance = accountFrom.balance.Sub(amount)
	accountTo.balance = accountFrom.balance.Add(amount)
	return true
}

func main() {
	// initialize bank account array
	var bankAccounts = make([]BankAccount, 100)
	for i := 0; i < len(bankAccounts); i++ {
		bankAccounts[i].balance, _ = decimal.NewFromString("1000")
	}
	// setup wait group
	var waiter = sync.WaitGroup{}
	waiter.Add(1000)
	for i := 0; i < 1000; i++ {
		go func() {
			defer waiter.Done()
			// we don't know which index is going to be larger, so this will cause a deadlock if two transfers in
			// opposite directions happen at the same time or several transfers that make a cycle happen at the same
			// time
			var indexFrom = rand.Intn(100)
			var indexTo = rand.Intn(100)
			amount, _ := decimal.NewFromString("10")
			Transfer(&bankAccounts[indexFrom], &bankAccounts[indexTo], amount) // possible deadlock here
		}()
	}
	waiter.Wait()
}
