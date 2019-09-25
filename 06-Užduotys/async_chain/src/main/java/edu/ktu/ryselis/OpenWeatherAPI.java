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

/**
 * A class that encapsulates communication with OpenWeather service
 */
class OpenWeatherAPI {
    private String apiKey;

    OpenWeatherAPI() {
        // sets API key from api_key.txt file. One should register for the key at OpenWeather web page
        try {
            byte[] encoded = Files.readAllBytes(Paths.get("api_key.txt"));
            apiKey = new String(encoded, Charset.defaultCharset());
        } catch (IOException e) {
            apiKey = null;
        }
    }

    /**
     * Makes a request to download current temperature for a city
     * @param cityId - ID of the city to get temperature for
     * @return JSON returned by OpenWeather
     * @throws IOException if failed to connect to OpenWeather service
     */
    private String makeOpenWeatherRequest(int cityId) throws IOException {
        // url should look like this: http://api.openweathermap.org/data/2.5/weather?id=<cityId>&appid=<apiKey>
        String apiRoot = "http://api.openweathermap.org/";
        URL url = new URL(apiRoot + "data/2.5/weather?id=" + cityId + "&appid=" + apiKey);
        // make HTTP request
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("GET");
        // get response to our request, it should be in JSON format and may consist of multiple lines
        BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));
        // get all lines and join them into a single string
        String content = reader.lines().collect(Collectors.joining());
        // dispose open resources
        reader.close();
        conn.disconnect();
        return content;
    }

    /**
     * Given the full JSON response from OpenWeather API, extract temperature as a double
     * @param jsonResponse - full response retrieved from OpenWeather API
     * @return current temperature
     * @throws ParseException if JSON passed into the method was invalid
     */
    private double parseResponse(String jsonResponse) throws ParseException {
        JSONParser parser = new JSONParser();
        JSONObject object = (JSONObject) parser.parse(jsonResponse);
        JSONObject main = (JSONObject) object.get("main");
        return (double) main.get("temp");
    }

    /**
     * Convert kelvins to degrees Celsius
     * @param kelvins - temperature in kelvins
     * @return temperature in Celsius
     */
    private double kelvinToCelsius(double kelvins) {
        return kelvins - 273.15;
    }

    /**
     * Given city ID, return a future that will resolve to current temperature in that city
     * @param cityId - ID of the city
     * @return - future containing current temperature in the city
     */
    CompletableFuture<Double> getTemperatureAsync(int cityId){
        // result is retrieved by making request to OpenWeather, parsing response and converting temperature to Celsius
        return CompletableFuture.supplyAsync(() -> {  // start of future chain
            try {
                return this.makeOpenWeatherRequest(cityId);  // step 1. make request and get response
            } catch (IOException e) {
                return null;
            }
        }).thenApply(res -> {
            try {
                return this.parseResponse(res);  // step 2. get response and parse temperature
            } catch (ParseException e) {
                return null;
            }
        }).thenApply(this::kelvinToCelsius);  // step 3. get temperature in kelvins and convert it to Celsius
    }
}
