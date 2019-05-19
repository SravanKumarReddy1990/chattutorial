var layerWFS=new ol.layer.Vector({
              title: 'added Layer',
              source:  new ol.source.Vector({
  			url: 'http://localhost:8080/sam/andrapradesh.geojson',
  			format: new ol.format.GeoJSON(),
			projection:"EPSG:4326"
			})
		});

var map = new ol.Map({
    target: 'map',
    layers: [
        new ol.layer.Tile({
            source: new ol.source.OSM()
        }),
        layerWFS
    ],
    view: new ol.View({
        center: ol.proj.transform([78.1621435,16.5087274], 'EPSG:4326', 'EPSG:3857'),
        zoom: 50
    })
});

function checData(){
 //var point= new ol.geom.Point(ol.proj.transform(, 'EPSG:4326', 'EPSG:3857'))
//var input=layerWFS.getSource().getFeaturesAtCoordinate(point);

var coord = ol.proj.fromLonLat([78.1621435,16.5087274]);
var features=layerWFS.getSource().getFeatures();	
features.forEach(function(feature){ 
var polygon_extent=feature.getGeometry().getExtent();
var att = feature.getProperties();
  var contains = ol.extent.containsCoordinate(polygon_extent, coord);
  console.info(contains+" , "+att.ac_name);
});
}
