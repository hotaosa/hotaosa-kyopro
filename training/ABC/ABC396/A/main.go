package main

import "fmt"

func main() {
	var n int
	fmt.Scan(&n)
	a := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&a[i])
		if i >= 2 && a[i-1] == a[i] && a[i-2] == a[i] {
			fmt.Println("Yes")
			return
		}
	}
	fmt.Println("No")
}
