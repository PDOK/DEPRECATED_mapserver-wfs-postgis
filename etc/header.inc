  IMAGETYPE             png
  EXTENT                10000 300000 280000 625000
  UNITS                 meters
  MAXSIZE               4000
  SIZE                  540 650   # Only used for preview
  STATUS                ON
  DEBUG                 5 
  CONFIG  "MS_ERRORFILE" "stderr"

  WEB
    METADATA
      "ows_enable_request"               "*"
      "ows_fees"                         "NONE"
      "ows_accessconstraints"            "otherRestrictions; http://creativecommons.org/publicdomain/mark/1.0/deed.nl"
      "ows_contactorganization"          "PDOK"
      "ows_service_onlineresource"       "https://www.pdok.nl"
      "ows_contactperson"                "KlantContactCenter PDOK"
      "ows_contactposition"              "pointOfContact"
      "ows_contactvoicetelephone"        ""
      "ows_contactfacsimiletelephone"    ""
      "ows_addresstype"                  "Work"
      "ows_address"                      ""
      "ows_city"                         "Apeldoorn"
      "ows_stateorprovince"              ""
      "ows_postcode"                     ""
      "ows_country"                      "Nederland"
      "ows_contactelectronicmailaddress" "BeheerPDOK@kadaster.nl"
      "ows_hoursofservice"               ""
      "ows_contactinstructions"          ""
      "ows_role"                         ""
      "ows_srs"                          "EPSG:28992 EPSG:25831 EPSG:25832 EPSG:3034 EPSG:3035 EPSG:3857 EPSG:4258 EPSG:4326 CRS:84"
      "wfs_encoding"                     "UTF-8"
      "wfs_maxfeatures"                  "15000"
      "wfs_getfeature_formatlist"        "geojson,json"
    END # METADATA
  END # WEB

  RESOLUTION 96
  DEFRESOLUTION 96

  PROJECTION
    "init=epsg:28992"
  END

  OUTPUTFORMAT
    NAME "geojson"
    DRIVER "OGR/GEOJSON"
    MIMETYPE "application/json; subtype=geojson"
    FORMATOPTION "STORAGE=stream"
    FORMATOPTION "FORM=SIMPLE"
  END

  OUTPUTFORMAT
    NAME "json"
    DRIVER "OGR/GEOJSON"
    MIMETYPE "application/json"
    FORMATOPTION "STORAGE=stream"
    FORMATOPTION "FORM=SIMPLE"
  END
