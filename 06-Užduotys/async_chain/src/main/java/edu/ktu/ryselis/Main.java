package edu.ktu.ryselis;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;
import java.util.stream.Collectors;

public class Main {

    /**
     * A program that queries current temperature of several different cities asynchronously and prints them to console
     */
    public static void main(String[] args) {
        // weather is going to be retrieved from OpenWeather service. It is access using OpenWeatherAPI class
	    OpenWeatherAPI api = new OpenWeatherAPI();
	    // create a hashmap with keys being city IDs in OpenWeather services, values - city names
        Map<Integer, String> cities = new HashMap<>();
        cities.put(598098, "Klaipėda");
        cities.put(593116, "Vilnius");
        cities.put(596128, "Panevėžys");
        cities.put(597231, "Marijampolė");
        cities.put(598316, "Kaunas");
        List<CompletableFuture<Void>> completableFutures = cities.keySet()  // keySet is all keys of hashmap (city IDs)
                .stream()  // convert to stream so we can use map
                .map(id -> api.getTemperatureAsync(id)  // get temperature asynchronously
                        // when result is calculated, print it to console
                        .thenAccept(res -> System.out.println(cities.get(id) + ": " + res)))
                .collect(Collectors.toList());  // put all generated futures to a list
        // create a combined future so we can use it to wait for all combined futures at once
        CompletableFuture<Void> combinedFutures = CompletableFuture
                .allOf(completableFutures.toArray(new CompletableFuture[cities.size()]));
        try {
            // wait for all tasks to complete
            combinedFutures.get();
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }
    }
}
