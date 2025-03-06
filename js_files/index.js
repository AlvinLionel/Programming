var myInterval = setInterval(function () {
    document.getElementById("time").innerHTML = Date();
    document.getElementById("time").style.color = "lightgreen";
}, 1000);

document.addEventListener("DOMContentLoaded", function () {
    const name = prompt("Enter your name: ");
    var length = name.length;
    var newInterval=setInterval(function (){
        let num = Math.floor(Math.random() * length) + 1;
        document.getElementById("demo").innerHTML=name.slice(num);
    },1000);
}) 
if (confirm("Do you love me: ")) {
    alert("Thank you,I love you too.");
} else {
    alert("Why not?");

}