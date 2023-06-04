# LoRa Mesh Network Interface Specification
This interface uses LoRa and MQTT for communication. Each node uses LoRa to send and receive packets.

## Messages
Each package contains at least:
- topic: The MQTT topic
- payload: The field that holds the data including these fields
  - sender uuid: A uuid of the node that initially sent the message
  - timestamp: The unix timestamp for when the message was sent

Using the following format:
```
  {
    "topic": "esp32/sample-topic",
    "uuid": "aabbccdd",
    "messageTimestamp": "1685640553",
  }
```

A sample of the full JSON would look like this:
```
   {
     "topic": "esp32/sample-topic",
     "uuid": "aabbccdd",
     "messageTimestamp": "1685640553",
     "content": {
      ...(content),
     }
   }
```

## Interface

The interface uses JSON for its payload.

## Topics

All the topics are filled with sample data

### System data

Information about a specific mesh node

#### Update ID
Topic:
```
v1/backend/measurements
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
      "type": "update-id",
      "value": "0cd1852e-196b-4e2a-a398-6ae835d0caee",
  }
}
```

#### Health status
Topic:
```
v1/backend/measurements/
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
      "type": "health-status",
      "value": "1685640553",
  }
}
```

#### Battery status
Topic:
```
v1/backend/measurements/
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
      "type": "battery-status",
      "value": "69"
  }
}
```

#### Signal strength
Topic:
```
v1/backend/measurements/
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
      "type": "signal-strength",
      "value": "-78.4"
  }
}
```

### Sensor Data

Still unsure if approach is good enough. It might be better to research and check if generic sensor data payload would be valid.

Topic for all sensors:
```
v1/sensors
```

#### Camera

Topic:
```
v1/sensors/
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
        "uuid": "cam/MAC",
        "data": "200"
  }
}
```
