package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
)

var thirdPartyPrefixes = []string{
	"atcoder/",
	"Eigen/",
}

func isThirdPartyInclude(line string) bool {
	for _, prefix := range thirdPartyPrefixes {
		if strings.Contains(line, "<"+prefix) {
			return true
		}
	}
	return false
}

func isUserInclude(line string) bool {
	return strings.Contains(line, "\"")
}

func main() {
	var stdIncludes []string
	var thirdPartyIncludes []string
	var userIncludes []string
	var contents []string
	scanner := bufio.NewScanner(os.Stdin)

	for scanner.Scan() {
		line := scanner.Text()
		if strings.HasPrefix(line, "#line") {
			continue
		}
		if strings.HasPrefix(line, "#include") {
			if isThirdPartyInclude(line) {
				thirdPartyIncludes = append(thirdPartyIncludes, line)
			} else if isUserInclude(line) {
				userIncludes = append(userIncludes, line)
			} else {
				stdIncludes = append(stdIncludes, line)
			}
		} else {
			contents = append(contents, line)
		}
	}

	sort.Strings(stdIncludes)
	sort.Strings(thirdPartyIncludes)
	sort.Strings(userIncludes)

	for _, inc := range stdIncludes {
		fmt.Println(inc)
	}
	if len(stdIncludes) > 0 {
		fmt.Println()
	}
	for _, inc := range thirdPartyIncludes {
		fmt.Println(inc)
	}
	if len(thirdPartyIncludes) > 0 {
		fmt.Println()
	}
	// for _, inc := range userIncludes {
	// 	fmt.Println(inc)
	// }
	// if len(userIncludes) > 0 {
	// 	fmt.Println()
	// }

	prevIsEmpty := true
	for _, content := range contents {
		if content == "" || content == "//" {
			if !prevIsEmpty {
				fmt.Println()
			}
			prevIsEmpty = true
		} else {
			prevIsEmpty = false
			fmt.Println(content)
		}
	}
}
