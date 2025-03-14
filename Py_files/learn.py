import tkinter as tk
from tkinter import messagebox

# Function to read users from file
def load_users():
    users = {}
    try:
        with open("..Others/Users.txt", "r") as file:
            for line in file:
                parts = line.strip().split(',')
                username = parts[1]
                users[username] = {
                    "name": parts[0],
                    "password": parts[2],
                    "balance": float(parts[3])
                }
    except FileNotFoundError:
        pass
    return users

# Function to read transactions from file
def load_transactions():
    transactions = []
    try:
        with open("../Others/Transactions.txt", "r") as file:
            for line in file:
                parts = line.strip().split(',')
                transactions.append({
                    "username": parts[0],
                    "type": parts[1],
                    "amount": float(parts[2])
                })
    except FileNotFoundError:
        pass
    return transactions

# Function to save users to file
def save_users(users):
    with open("../Others/Users.txt", "w") as file:
        for username, data in users.items():
            file.write(f"{data['name']},{username},{data['password']},{data['balance']}\n")#Modify this function to save the user data in the correct format

# Function to save transactions to file
def save_transactions(transactions):
    with open("../Others/Transactions.txt", "w") as file:
        for transaction in transactions:
            file.write(f"{transaction['username']},{transaction['type']},{transaction['amount']}\n")

# Create GUI
def create_account():
    def submit():
        name = name_entry.get()
        username = username_entry.get()
        password = password_entry.get()
        balance = 0.0
        if username in users:
            messagebox.showerror("Error", "Username already exists.")
        else:
            users[username] = {"name": name, "password": password, "balance": balance}
            save_users(users)
            messagebox.showinfo("Success", "Account created successfully.")
            create_account_window.destroy()

    create_account_window = tk.Toplevel(root)
    create_account_window.title("Create Account")

    tk.Label(create_account_window, text="Name").pack()
    name_entry = tk.Entry(create_account_window)
    name_entry.pack()

    tk.Label(create_account_window, text="Username").pack()
    username_entry = tk.Entry(create_account_window)
    username_entry.pack()

    tk.Label(create_account_window, text="Password").pack()
    password_entry = tk.Entry(create_account_window, show="*")
    password_entry.pack()

    tk.Button(create_account_window, text="Submit", command=submit).pack()

def login():
    def submit():
        username = username_entry.get()
        password = password_entry.get()
        if username in users and users[username]["password"] == password:
            messagebox.showinfo("Success", f"Welcome {users[username]['name']}!")
            login_window.destroy()
            show_account_actions(username)
        else:
            messagebox.showerror("Error", "Invalid username or password.")

    login_window = tk.Toplevel(root)
    login_window.title("Login")

    tk.Label(login_window, text="Username").pack()
    username_entry = tk.Entry(login_window)
    username_entry.pack()

    tk.Label(login_window, text="Password").pack()
    password_entry = tk.Entry(login_window, show="*")
    password_entry.pack()

    tk.Button(login_window, text="Submit", command=submit).pack()

def show_account_actions(username):
    def deposit():
        def submit():
            amount = float(amount_entry.get())
            users[username]["balance"] += amount
            transactions.append({"username": username, "type": "Deposit", "amount": amount})
            save_users(users)
            save_transactions(transactions)
            messagebox.showinfo("Success", f"${amount} deposited successfully.")
            deposit_window.destroy()

        deposit_window = tk.Toplevel(root)
        deposit_window.title("Deposit")

        tk.Label(deposit_window, text="Amount").pack()
        amount_entry = tk.Entry(deposit_window)
        amount_entry.pack()

        tk.Button(deposit_window, text="Submit", command=submit).pack()

    def withdraw():
        def submit():
            amount = float(amount_entry.get())
            if users[username]["balance"] >= amount:
                users[username]["balance"] -= amount
                transactions.append({"username": username, "type": "Withdraw", "amount": amount})
                save_users(users)
                save_transactions(transactions)
                messagebox.showinfo("Success", f"${amount} withdrawn successfully.")
                withdraw_window.destroy()
            else:
                messagebox.showerror("Error", "Insufficient balance.")

        withdraw_window = tk.Toplevel(root)
        withdraw_window.title("Withdraw")

        tk.Label(withdraw_window, text="Amount").pack()
        amount_entry = tk.Entry(withdraw_window)
        amount_entry.pack()

        tk.Button(withdraw_window, text="Submit", command=submit).pack()

    def check_balance():
        balance = users[username]["balance"]
        messagebox.showinfo("Balance", f"Your balance is ${balance}.")

    account_actions_window = tk.Toplevel(root)
    account_actions_window.title("Account Actions")

    tk.Label(account_actions_window, text=f"Welcome {users[username]['name']}!").pack()
    tk.Button(account_actions_window, text="Deposit", command=deposit).pack()
    tk.Button(account_actions_window, text="Withdraw", command=withdraw).pack()
    tk.Button(account_actions_window, text="Check Balance", command=check_balance).pack()

# Main Application
users = load_users()
transactions = load_transactions()

root = tk.Tk()
root.title("Banking System")

tk.Button(root, text="Create Account", command=create_account).pack()
tk.Button(root, text="Login", command=login).pack()

root.mainloop()
