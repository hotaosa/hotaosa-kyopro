package main

import (
	"fmt"
	"strings"
)

func main() {
	var s string
	fmt.Scan(&s)
	fmt.Println(len(strings.Replace(s, "io", "", -1)))
}
