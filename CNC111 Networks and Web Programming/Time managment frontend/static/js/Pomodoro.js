var timer;
var timerString;
var prevMode = 0;
var currentTime;
var currentCount = 1;
var actualCount = 1;
var startBTN;

window.onload = () => {
  document.getElementById("focus-btn").onclick = changeToFocus;
  document.getElementById("shortb-btn").onclick = changeToSB;
  document.getElementById("longb-btn").onclick = changeToLB;
  startBTN = document.getElementById("startBTN");
  startBTN.onclick = startModeTimer;

  timerString = document.getElementById("timer-string");
  changeToFocus();

  var rmbtns = document.getElementsByClassName("remove-item-btn");

  Array.from(rmbtns).forEach((btn) => {
    btn.addEventListener("click", () => {
      document.getElementById("schedule-list").removeChild(btn.parentElement);
    });
  });
};

function changeToFocus() {
  timerString.innerHTML = "25:00";
  currentTime = 25 * 60;
  prevMode = 0;
  resetTimer();
}

function changeToSB() {
  timerString.innerHTML = "5:00";
  currentTime = 5 * 60;
  prevMode = 1;
  resetTimer();
}

function changeToLB() {
  timerString.innerHTML = "15:00";
  currentTime = 15 * 60;
  prevMode = 2;
  resetTimer();
}

function startModeTimer() {
  if (!timer) {
    timer = setInterval(updateTimerString, 1000);
    startBTN.disabled = true;
  }
}

function updateTimerString() {
  if (currentTime > 0) {
    console.log(currentTime);
    currentTime--;
    var minutes = Math.floor(currentTime / 60);
    var seconds = currentTime % 60;
    timerString.innerHTML = minutes.toString() + ":" + seconds.toString();
  } else {
    if (prevMode == 0) {
      currentCount += 1;
      actualCount += 1;
      updateCurrentCountString();
    }
    clearInterval(timer);
    timer = null;
    startBTN.disabled = false;
    if (prevMode == 0 && actualCount == 5) {
      actualCount = 0;
      changeToLB();
    } else if (prevMode == 1 || prevMode == 2) {
      changeToFocus();
    } else if (prevMode == 0) {
      changeToSB();
    }
  }
}

function updateCurrentCountString() {
  document.getElementById("timer-count-string").innerHTML =
    "#" + currentCount.toString();
}

function resetTimer() {
  if (timer) {
    clearInterval(timer);
    timer = null;
    startBTN.disabled = false;
  }
}
