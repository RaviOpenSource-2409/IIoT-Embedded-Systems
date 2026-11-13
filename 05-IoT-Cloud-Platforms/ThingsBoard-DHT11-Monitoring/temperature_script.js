var temp = Number(msg.temperature);
var hum  = Number(msg.humidity);

// 1) Validate data
if (isNaN(temp) || isNaN(hum)) {
    msg.sw = false;
    msg.info = "Invalid sensor data";
}
// DHT11 range: 0-50 C, 20-90 % RH
else if (temp < 0 || temp > 50 || hum < 20 || hum > 90) {
    msg.sw = false;
    msg.info = "Sensor value out of range";
}
// 2) Custom logic
else if (temp > 26) {
    msg.sw = true;
    msg.info = "Env is HOT";
} else {
    msg.sw = false;
    msg.info = "Env is normal";
}

return {msg: msg, metadata: metadata, msgType: msgType};
