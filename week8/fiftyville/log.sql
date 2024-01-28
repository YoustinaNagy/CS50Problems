
-- license_plate | minute |
-- +---------------+--------+
-- | 5P2BI95       | 16     |
-- | 94KL13X       | 18     |
-- | 6P58WS2       | 18     |
-- | 4328GD8       | 19     |
-- | G412CB7       | 20     |
-- | L93JTIZ       | 21     |
-- | 322W7JE       | 23     |
-- | 0NTHK55       | 23     |
-- | 1106N58       | 35     |
-- +---------------+--------+
-- account_number |
-- +----------------+
-- | 28500762       |
-- | 28296815       |
-- | 76054385       |
-- | 49610011       |
-- | 16153065       |
-- | 25506511       |
-- | 81061156       |
-- | 26013199       |
-- +----------------+

-- +---------------+
-- | license_plate |
-- +---------------+
-- | 5P2BI95       |
-- | 94KL13X       |
-- | 6P58WS2       |
-- | 4328GD8       |
-- | G412CB7       |
-- | L93JTIZ       |
-- | 322W7JE       |
-- | 0NTHK55       |
-- | 1106N58       |
-- +---------------+



-- Keep a log of any SQL queries you execute as you solve the mystery.
-- id
-- abbreviation
-- full_name
-- city


-- tables:

--airports               crime_scene_reports       people
-- atm_transactions      flights                   phone_calls
-- bakery_security_logs  interviews
-- bank_accounts         passengers


-- INFO:
-- that the theft took place on July 28, 2021 and that it took place on Humphrey Street.

-- The town of Fiftyville has called upon you to solve the mystery of the stolen duck.




-- crime scene report
SELECT id, description FROM crime_scene_reports WHERE street = "Humphrey Street" AND year = 2021 AND month = 7 AND day = 28 ;


-- crime descriptin
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time –
-- each of their interview transcripts mentions the bakery.

-- id:  295



-- interviews:
SELECT * FROM interviews WHERE transcript LIKE "%bakery%";

-- 3 transcriptS:

-- id 161:
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot
-- in that time frame.
SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour =10 AND activity = "exit" ;

SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour =10 AND activity = "exit" ;




-- id 162:
-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- to get account_numbers:

SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";


-- to get the common person who withdaw money and get out of the parking:

-- to get the id withdraw the money
SELECT person_id FROM bank_accounts
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";



-- to get the id get out of the barking:
SELECT id FROM people WHERE license_plate = (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour =10 AND activity = "exit");

SELECT people.id FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND day = 28 AND hour =10 AND activity = "exit";


-- to get them both
SELECT person_id FROM bank_accounts
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw" AND bank_accounts.person_id IN(

SELECT people.id FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND day = 28 AND hour =10 AND activity = "exit"
);




-- id 163:
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.
SELECT Passport_number FROM passengers
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.origin_airport_id = airports.id
WHERE airports.full_name LIKE "%Fiftyville%" AND year = 2021 AND month = 7 AND day = 29 AND hour = 8;



person_id , people.name ,
-- the common betwen passengers AND withdraw and parking
SELECT people.phone_number FROM bank_accounts
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw" AND bank_accounts.person_id IN(

SELECT people.id FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND day = 28 AND hour =10 AND activity = "exit"
) AND people.passport_number IN (
SELECT Passport_number FROM passengers
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.origin_airport_id = airports.id
WHERE airports.full_name LIKE "%Fiftyville%" AND year = 2021 AND month = 7 AND day = 29 AND hour = 8
);




-- the call:
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND caller =(SELECT people.phone_number FROM bank_accounts
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw" AND bank_accounts.person_id IN(

SELECT people.id FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND day = 28 AND hour =10 AND activity = "exit"
) AND people.passport_number IN (
SELECT Passport_number FROM passengers
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.origin_airport_id = airports.id
WHERE airports.full_name LIKE "%Fiftyville%" AND year = 2021 AND month = 7 AND day = 29 AND hour = 8
));




The THIEF is:


-- in details
SELECT name FROM people WHERE phone_number = (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND caller IN (SELECT people.phone_number FROM bank_accounts
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw" AND bank_accounts.person_id IN(

SELECT people.id FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND day = 28 AND hour =10 AND activity = "exit"
) AND people.passport_number IN (
SELECT Passport_number FROM passengers
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.origin_airport_id = airports.id
WHERE airports.full_name LIKE "%Fiftyville%" AND year = 2021 AND month = 7 AND day = 29 AND hour = 8
))ORDER BY duration ASC LIMIT 1);






-- The city the thief ESCAPED TO:
SELECT full_name FROM airports WHERE id = (
SELECT flights.destination_airport_id FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
JOIN passengers ON flights.id = passengers.flight_id
Join people ON passengers.passport_number = people.passport_number
WHERE people.phone_number = "(286) 555-6063");












The ACCOMPLICE is:


-- in details
SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE caller IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND caller IN (
SELECT people.phone_number FROM bank_accounts
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw" AND bank_accounts.person_id IN(

SELECT people.id FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND day = 28 AND hour =10 AND activity = "exit"
) AND people.passport_number IN (
SELECT Passport_number FROM passengers
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.origin_airport_id = airports.id
WHERE airports.full_name LIKE "%Fiftyville%" AND year = 2021 AND month = 7 AND day = 29 AND hour = 8
))ORDER BY duration ASC LIMIT 1));









-- The THIEF is:
-- SELECT name FROM people WHERE phone_number = "(286) 555-6063";


-- The city the thief ESCAPED TO:
-- SELECT full_name FROM airports WHERE id = 4 ;


-- The ACCOMPLICE is:
-- SELECT name FROM people WHERE phone_number = "(676) 555-6554";





















-- SELECT id FROM airports WHERE full_name LIKE "%Fiftyville%";

-- SELECT * FROM flights WHERE origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29;