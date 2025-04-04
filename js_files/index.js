var showDate = setInterval(function () {
    document.getElementById("date").innerHTML = Date();
    document.getElementById("date").style.color = "lightgreen";
}, 1000);
var randomNUm = setInterval(function () {
    document.getElementById("rand").innerHTML = (Math.random() * 100000).toFixed(5);
}, 500)

/* function playRPS() {
    let userPick = document.getElementById("rps").value;
    if (userPick == "") {
        alert("Please enter your pick");
        return;
    }
    let arr = ["rock", "paper", "scissors"];
    let compPick = arr[Math.floor(Math.random() * 3)];
    if (userPick == compPick) {
        document.getElementById("compPick").innerHTML = compPick;
        alert("It's a draw");
    } else if (userPick == "rock") {
        if (compPick == "paper") {
            document.getElementById("compPick").innerHTML = compPick;
            alert("Computer wins");
        } else {
            document.getElementById("compPick").innerHTML = compPick;
            alert("You lose");
        }
    } else if (userPick == "paper") {
        if (compPick == "scissors") {
            document.getElementById("compPick").innerHTML = compPick;
            alert("You lose");
        }
        else {
            document.getElementById("compPick").innerHTML = compPick;
            alert("You win");
        }
    } else if (userPick == "scissors") {
        if (compPick == "rock") {
            document.getElementById("compPick").innerHTML = compPick;
            alert("You lose")
        }
        else {
            document.getElementById("compPick").innerHTML = compPick;
            alert("You win");
        }
    }
} */

const myArray=[1,2,3,4,5];
let myString=myArray.join();
console.log(myArray);
console.log(myString);
let newArray=myString.split('-');
console.log(newArray);
