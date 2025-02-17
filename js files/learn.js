var myInterval = setInterval(function () {
    document.getElementById("time").innerHTML = Date();
},1000);
class Fruit {
    constructor(fruitName, fruitColor) {
        this.name = fruitName;
        this.color = fruitColor;
        this.taste = "sweet";
    }
    showDetails() {
        document.getElementById("demo").innerHTML = "This " + fruit.name + " is " + fruit.color + " and is " + fruit.taste;
    }
}
const fruit = new Fruit("mango", "orange");
document.addEventListener("DOMContentLoaded",function(){
    fruit.showDetails();
})