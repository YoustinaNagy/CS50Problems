import os
import sqlite3
from datetime import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    result = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
    print(result)
    username= result[0]["username"]

    records=db.execute("SELECT symbol, SUM(shares) AS shares ,SUM(total_price) AS total_price ,stock_name FROM portfolio WHERE user_id = ? GROUP BY symbol", session["user_id"])
    # print(records)
    for record in records:
        symbol=record["symbol"]
        info=lookup(symbol)
        record["current_price"]=info["price"]


    result = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash= result[0]["cash"]

    return render_template("index.html", username=username , records=records ,cash=cash)

    #     shares_bought =db.execute("SELECT SUM (shares) AS sum FROM portfolio WHERE user_id = ? AND symbol=? AND type ='buy'", session["user_id"],symbol)
    #     shares_sold = db.execute("SELECT SUM (shares) AS sum FROM portfolio WHERE user_id = ? AND symbol=? AND type ='sell'", session["user_id"],symbol)
    #     # print(shares_sold , shares)

    #     shares_bought = shares_bought[0]['sum'] if shares_bought[0]['sum'] else 0
    #     shares_sold = shares_sold[0]['sum'] if shares_sold[0]['sum'] else 0
    #     net_shares = shares_bought -shares_sold






@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method =='POST':
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol or not shares:
            return apology("must provide a stock's symbol and shares", 404)

        info=lookup(symbol)


        if not info:
            return apology('The requested Stock symbol does not exist!!')

        try:
            if int(shares) <= 0:
                return apology("must provide a positive number for stock's shares", 400)
        except Exception as e:
            return apology("Error parsing stock's shares, please provide 0a positive integer", 400)

        stock_price = int(shares)*info["price"]
        stock_name=info["name"]
        # print(stock_price)
        result = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash= result[0]["cash"]
        # print(cash)
        if stock_price > cash:
            return apology("Your balance is not suffecint to buy the stocks", 400)

        db.execute("INSERT INTO portfolio (user_id,symbol,shares, type,total_price,transaction_date,date,stock_name) VALUES (?,?,?,'buy',?,TIME(),DATE(),?)", session["user_id"],symbol,shares,stock_price,stock_name)
        db.execute("UPDATE users SET cash = ? WHERE id = ?" ,cash - stock_price,session["user_id"])
        # Commit the changes and close the connection
        # conn.commit()
        # conn.close()
        # conn = sqlite3.connect('finance.db')
        # cursor = conn.cursor()
        # # Get the current time and date
        # current_time = datetime.now().strftime('%H:%M:%S')
        # current_date = datetime.now().strftime('%Y-%m-%d')

        # Insert the time and date into the table
        # cursor.execute("INSERT INTO portfolio (time, date) VALUES (?, ?)", (current_time, current_date))
        return redirect('/')



    return render_template('buy.html')
    # """Buy shares of stock"""
    # def quote():
    # """Get stock quote."""
    #     if request.method == 'POST':
        # symbol = request.form.get("symbol")

        # if not symbol:
        #     return apology("must provide a dtock's symbol", 403)

        # # TODO
        # info = lookup(symbol)
        # if not info:
        #     return appolgy('The requested Stock symbol does not exist!!')

        # return render_template('quoted.html', info=info)






@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    result = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
    username= result[0]["username"]
    records=db.execute("SELECT symbol , abs(shares) AS shares ,abs(total_price) AS total_price , type , transaction_date , date ,stock_name FROM portfolio WHERE user_id = ?", session["user_id"])

    print(records)


    return render_template("history.html", username=username , records=records)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == 'POST':
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("must provide a stock's symbol", 400)

        # TODO
        info = lookup(symbol)
        if not info:
            return apology('The requested Stock symbol does not exist!!')

        return render_template('quoted.html', info=info)


    return render_template('quote.html')


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == 'POST':
        # Ensure username was submitted
        name = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not name or not password:
            return apology("must provide username and password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(rows) > 0:
            return apology("username already exists", 400)

        if password != confirmation:
            return apology("passord and confirmation must match", 400)

        password_hash = generate_password_hash(password)

        db.execute("INSERT INTO users(username, hash) VALUES (?, ?)", request.form.get("username"), password_hash)

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        session["user_id"] = rows[0]["id"]

        return redirect('/')

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method =='POST':
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol or not shares:
            return apology("must provide a stock's symbol and shares", 404)

        info=lookup(symbol)
        # print(info)

        if not info:
            return apology('The requested Stock symbol does not exist!!')

        try:
            if int(shares) <= 0:
                return apology("must provide a positive number for stock's shares", 400)
        except Exception as e:
            return apology("Error parsing stock's shares, please provide 0a positive integer", 500)

        shares_bought =db.execute("SELECT SUM (shares) AS sum FROM portfolio WHERE user_id = ? AND symbol=? AND type ='buy'", session["user_id"],symbol)
        shares_sold = db.execute("SELECT SUM (shares) AS sum FROM portfolio WHERE user_id = ? AND symbol=? AND type ='sell'", session["user_id"],symbol)
        # print(shares_sold , shares)

        shares_bought = shares_bought[0]['sum'] if shares_bought[0]['sum'] else 0
        shares_sold = shares_sold[0]['sum'] if shares_sold[0]['sum'] else 0


        if shares_sold + int(shares) > shares_bought:
            return apology("sorry ,you don't have the required stocks to sell", 400)


        stock_price = int(shares)*info["price"]
        stock_name=info["name"]
        db.execute("INSERT INTO portfolio (user_id,symbol,shares, type,total_price,transaction_date,date,stock_name) VALUES (?,?,?,'sell',?,TIME(),DATE(),?)", session["user_id"],symbol,-int(shares),-stock_price,stock_name)
        result = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash= result[0]["cash"]
        db.execute("UPDATE users SET cash = ? WHERE id = ?" , cash + stock_price,session["user_id"])

        return redirect('/')



# lw m444 posttt

    result = db.execute("SELECT DISTINCT symbol FROM portfolio WHERE user_id = ?", session["user_id"])
    stocks=[]
    for I in result:
        stocks.append(I['symbol'])



    return render_template("sell.html" , stocks=stocks )
