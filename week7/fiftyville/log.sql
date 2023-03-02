-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Opened whole table crime_scene_reports to see how big the table is
SELECT * FROM crime_scene_reports;

SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28;

SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;

SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';

SELECT * FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type LIKE '%withdraw%';

SELECT * FROM flights JOIN airports ON airports.id = flights.origin_airport_id WHERE year = 2021 AND month = 7 AND day = 29 AND hour < 12 AND airports.city = 'Fiftyville';

SELECT city FROM airports WHERE id IN (SELECT destination_airport_id FROM flights JOIN airports ON airports.id = flights.origin_airport_id WHERE year = 2021 AND month = 7 AND day = 29 AND hour < 12 AND airports.city = 'Fiftyville');

SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10;

SELECT * FROM passengers WHERE flight_id IN (SELECT flights.id FROM flights JOIN airports ON airports.id = flights.origin_airport_id WHERE year = 2021 AND month = 7 AND day = 29 AND hour < 12 AND airports.city = 'Fiftyville');

SELECT * FROM bakery_security_logs JOIN people ON people.license_plate = bakery_security_logs.license_plate JOIN suspect_passport_numbers ON suspect_passport_numbers.passport_number = people.passport_number WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10;