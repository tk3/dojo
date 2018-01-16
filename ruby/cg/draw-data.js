var list_data = document.getElementById("list-data")

var key = "sample";
var d = document.createElement("div");
var p = document.createElement("p");
p.innerHTML = "2017 " + key;

var g = document.createElement("div");
g.id = "cal-heatmap-" + key;

d.appendChild(p);
d.appendChild(g);

list_data.appendChild(d);

var cal = new CalHeatMap();
cal.init({
  start: new Date(2017, 1, 0),
  itemSelector: "#cal-heatmap-" + key,
  range: 12,
  domain: "month",
  legend: [1, 5, 15, 20, 30],
  data: data
});
