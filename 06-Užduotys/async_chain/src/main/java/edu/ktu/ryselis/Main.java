package edu.ktu.ryselis;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.CompletableFuture;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Main {

    public static void main(String[] args) {
	    OpenWeatherAPI api = new OpenWeatherAPI();
        Map<Integer, String> cities = new HashMap<>();
        cities.put(593116, "Vilnius");
        cities.put(596128, "Panevėžys");
        cities.put(597231, "Marijampolė");
        cities.put(598316, "Kaunas");
        List<CompletableFuture<Void>> completableFutures = cities.keySet().stream().map(id -> api.getTemperatureAsync(id).thenAccept(res -> System.out.println(cities.get(id) + ": " + res))).collect(Collectors.toList());
        CompletableFuture<Void> combinedFutures = CompletableFuture.allOf(completableFutures.toArray(new CompletableFuture[cities.size()]));
        while (!combinedFutures.isDone()) {

        }
    }
}
