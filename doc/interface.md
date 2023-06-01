# LoRa Mesh Network Interface Specification
This interface uses LoRa and MQTT for communication. Each node uses LoRa to send and receive packets.

## Messages
Each package contains at least:
- topic: The MQTT topic
- payload: The field that holds the data including these fields
  - sender uuid: A uuid of the node that initially sent the message
  - timestamp: The timestamp for when the message was sent

Using the following format:
```
  "head":{
    "topic": "esp32/sample-topic",
    "uuid": "aabbccdd",
    "messageTimestamp": "1685640553",
  }
```

A sample of the full JSON would look like this:
```
   {
    "head":{
      "topic": "esp32/sample-topic",
      "uuid": "aabbccdd",
      "messageTimestamp": "1685640553",
    },
    "content": {
      ...(content)
    }
   }
```

## Interface

The interface uses JSON for its payload.

## Topics

All the topics are filled with sample data

### System data

Information about a specific mesh node

#### Created at
Topic:
```
v1/backend/measurements/created-at
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "createdAt": {
      "type": "timestamp",
      "value": "1685640553"
    }
  }
}
```

#### Updated at
Topic:
```
v1/backend/measurements/updated-at
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "updatedAt": {
      "type": "timestamp",
      "value": "1685640553"
    }
  }
}
```

#### Update ID
Topic:
```
v1/backend/measurements/update-id
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "updateId": {
      "type": "int",
      "value": "1337"
    }
  }
}
```

#### Health status
Topic:
```
v1/backend/measurements/health-status
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "createdAt": {
      "type": "timestamp",
      "value": "1685640553"
    }
  }
}
```

#### Battery status
Topic:
```
v1/backend/measurements/battery-status
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "battery": {
      "type": "int",
      "value": "69"
    }
  }
}
```

#### Signal strength
Topic:
```
v1/backend/measurements/signal-strength
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "signalStrength": {
      "type": "float",
      "value": "500.3"
    }
  }
}
```

### System data

#### Created at
Topic:
```
v1/backend/measurements/created-at
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "createdAt": {
      "type": "timestamp",
      "value": "1685640553"
    }
  }
}
```

#### Updated at
Topic:
```
v1/backend/measurements/updated-at
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "updatedAt": {
      "type": "timestamp",
      "value": "1685640553"
    }
  }
}
```

#### Health status
Topic:
```
v1/backend/measurements/health-status
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "createdAt": {
      "type": "timestamp",
      "value": "1685640553"
    }
  }
}
```

#### Battery status
Topic:
```
v1/backend/measurements/battery-status
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "battery": {
      "type": "int",
      "value": "69"
    }
  }
}
```

#### Signal strength
Topic:
```
v1/backend/measurements/signal-strength
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "signalStrength": {
      "type": "float",
      "value": "500.3"
    }
  }
}
```

### Sensor Data

Still unsure if approach is good. Might be better to research and check if generic sensor data payload would be valid.

Topic für alle Sensoren:
```
v1/sensors
```

#### Camera

Topic:
```
v1/sensors/camera
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
      "sensor": {
        "uuid": "cam/MAC",
        "data": "200"
      }
  }
}
```
