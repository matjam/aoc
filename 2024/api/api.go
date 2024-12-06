package api

import (
	"fmt"
	"net/http"
	"os"

	"github.com/charmbracelet/log"
	"github.com/go-resty/resty/v2"
)

// https://adventofcode.com/2024/day/1/input

var _cache map[int]string

func GetInput(day int) (string, error) {
	err := os.Mkdir(".cache", 0750)
	if err != nil && !os.IsExist(err) {
		log.Fatalf("💣 %v", err)
	}

	cacheFileName := fmt.Sprintf(".cache/%v.txt", day)
	cachedData, err := os.ReadFile(cacheFileName)
	if err == nil {
		log.Infof("✔️ %v exists, returning data for day %v", cacheFileName, day)
		return string(cachedData), nil
	}

	if _cache == nil {
		_cache = make(map[int]string)
	}

	client := resty.New()
	url := fmt.Sprintf("https://adventofcode.com/2024/day/%v/input", day)
	resp, err := client.R().
		SetCookie(&http.Cookie{Name: "session", Value: os.Getenv("AOC_SESSION")}).
		Get(url)

	if err != nil {
		log.Fatalf("💣 failed to retrieve puzzle input: %v", err)
	}

	body := resp.String()
	log.Infof("✔️ retrieved puzzle input, %v bytes", len(body))
	_cache[day] = body

	os.WriteFile(cacheFileName, []byte(body), 0644)

	return body, nil
}
