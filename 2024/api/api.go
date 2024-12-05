package api

import (
	"encoding/json"
	"fmt"
	"net/http"
	"os"

	"github.com/charmbracelet/log"
	"github.com/go-resty/resty/v2"
)

// https://adventofcode.com/2024/day/1/input

var _cache map[int]string

func GetInput(day int) (string, error) {
	cache, err := os.ReadFile(".cache.json")
	if err == nil {
		log.Infof("✔️ .cache.json exists, checking if it contains data for day %v", day)
		// load the data from the cache and see if the day we want is there
		err := json.Unmarshal(cache, &_cache)
		if err == nil {
			if input, ok := _cache[day]; ok {
				log.Infof("✔️ found input data for day %v", day)
				return input, nil
			}
			log.Infof("❌ no input data for day %v", day)
		} else {
			log.Fatalf("❌ malformed cache file? consider deleting and retry: %v", err)
		}
	}

	if _cache == nil {
		_cache = make(map[int]string)
	}

	client := resty.New()
	url := fmt.Sprintf("https://adventofcode.com/2024/day/%v/input", day)
	resp, err := client.R().
		SetCookie(&http.Cookie{Name: "session", Value: os.Getenv("AOC_SESSION")}).
		Get(url)

	body := resp.String()

	log.Infof("✔️ retrieved puzzle input, %v bytes", len(body))

	_cache[day] = body

	cache, err = json.Marshal(_cache)
	if err != nil {
		log.Fatalf("❌ couldn't create cache json: %v", err.Error())
	}

	os.WriteFile(".cache.json", cache, 0644)

	return _cache[day], nil
}
