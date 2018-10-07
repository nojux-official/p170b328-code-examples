package edu.ktu.ryselis;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.concurrent.CompletableFuture;
import java.util.stream.Collectors;

class OpenWeatherAPI {
    private String apiKey;

    OpenWeatherAPI() {
        try {
            byte[] encoded = Files.readAllBytes(Paths.get("api_key.txt"));
            apiKey = new String(encoded, Charset.defaultCharset());
        } catch (IOException e) {
            apiKey = null;
        }
    }

    private String makeOpenWeatherRequest(int cityId) throws IOException {
        String apiRoot = "http://api.openweathermap.org/";
        URL url = new URL(apiRoot + "data/2.5/weather?id=" + cityId + "&appid=" + apiKey);
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("GET");
        BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));
        String content = reader.lines().collect(Collectors.joining());
        reader.close();
        conn.disconnect();
        return content;
    }

    private double parseResponse(String jsonResponse) throws ParseException {
        JSONParser parser = new JSONParser();
        JSONObject object = (JSONObject) parser.parse(jsonResponse);
        JSONObject main = (JSONObject) object.get("main");
        return (double) main.get("temp");
    }

    private double kelvinToCelsius(double kelvins) {
        return kelvins - 273.15;
    }

    CompletableFuture<Double> getTemperatureAsync(int cityId){
        return CompletableFuture.supplyAsync(() -> {
            try {
                return this.makeOpenWeatherRequest(cityId);
            } catch (IOException e) {
                return null;
            }
        }).thenApply(res -> {
            try {
                return this.parseResponse(res);
            } catch (ParseException e) {
                return null;
            }
        }).thenApply(this::kelvinToCelsius);
    }
}
