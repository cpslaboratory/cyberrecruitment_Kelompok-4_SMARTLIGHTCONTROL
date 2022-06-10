const toggle_btn = document.querySelector(".toggle-btn");
const searchButton = document.querySelector("#button-addon2");
const inputKeyword = document.querySelector(".input-keyword");

function changeTheme() {
    if(!document.body.classList.contains("dark")){
        document.body.classList.add("dark");
        toggle_btn.classList.replace("uil-moon","uil-brightness")   
    }
    else{
        document.body.classList.remove("dark");
        toggle_btn.classList.replace("uil-brightness","uil-moon")
    }
}

toggle_btn.addEventListener("click", () => {
    changeTheme();
});


searchButton.addEventListener("click", function () {
  fetch(
    "https://api.openweathermap.org/data/2.5/weather?q=" +
      inputKeyword.value +
      "&appid=33e6c83b1aa000c5084bccf0613aa321&units=metric"
  )
    .then((response) => response.json())
    .then((response) => {
      let result = document.querySelector(".result");

      result.innerHTML = `<h2 style="margin-bottom: 15px;">${response.name}, ${response.sys.country}</h2>
                                <h5><span class="temp">${response.main.temp}°С</span> <span class="temp">${response.weather[0].description}</span></h5>
                                <p style="margin-bottom: 17px font-size: 10 px;">Temperature from ${response.main.temp_min}°С to ${response.main.temp_max}°С</p>
                                <h5>Wind Speed : ${response.wind.speed} m/s</h5>
                                <h5 style="margin-bottom: 17px;">Clouds : ${response.clouds.all}%</h5>
                                <h4 style="color: #012443;">Geo Coordinates : [${response.coord.lat}, ${response.coord.lon}]</h4>`;
    });
  inputKeyword.value = null;
});

function showTime() {
    var date = new Date();
    var h = date.getHours();
    var m = date.getMinutes();
    var s = date.getSeconds();
    var session = "AM";

    if (h >= 12) {
      h = h - 12;
      session = "PM";
    }
    if (h == 0) {
      h = 12;
    }
    h = h < 10 ? "0" + h : h;
    m = m < 10 ? "0" + m : m;
    s = s < 10 ? "0" + s : s;
    var time = h + ":" + m + ":" + s + " " + session;
    document.getElementById("myclock").innerText = time;
    document.getElementById("myclock").textContent = time;

    setTimeout(showTime, 1000);
  }
  showTime();