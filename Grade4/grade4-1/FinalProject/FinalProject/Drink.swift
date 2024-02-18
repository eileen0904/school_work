//
//  Drink.swift
//  FinalProject
//
//  Created by 張芯翎 on 2023/12/16.
//

import Foundation
import FirebaseFirestore
import FirebaseFirestoreSwift
import FirebaseAuth

class GetData: ObservableObject {
    @Published var user_name: String = "n"
    @Published var fav_path: String = "n"
    @Published var order_path: String = "n"
    
    init() {
        setName()
        setFavpath()
        setOrderpath()
    }
    
    func setName(){
        if let user = Auth.auth().currentUser{
            user_name = user.displayName ?? ""
            if user_name != nil{
                print("User:\(user_name)")
            }

        }
    }
    
    func setFavpath(){
        fav_path = "user/" + user_name + "/favorite"
    }
    
    func setOrderpath(){
        order_path = "user/" + user_name + "/order"
    }
}


class AllDrinks: ObservableObject{

    @Published var allDrinks = [Drink]()
    @Published var orders = [Drink]()
    @Published var total = 0
    
    func calTotal(){
        total = 0
        for i in orders.indices{
            total += orders[i].price
        }
    }
    
    // clear placed orders
    func removeOrder(){
        orders.removeAll()
        total = 0
    }
    
    // revise favorite data
    func modifyFavorite(user_name: String, name: String, isFav: Bool) {
        let db = Firestore.firestore()
        if isFav == true{ // add to favorite list
            do{
                let favorite = Favorite(name: name)
                try db.collection("user").document(user_name).collection("favorite").document(name).setData(from: favorite)
                print("modifyFavorite Add Success")
            } catch {
                print(error)
            }
        }
        else{ // delete from favorite list
            let collectionRef = db.collection("user").document(user_name).collection("favorite")
            let query = collectionRef.whereField("name", isEqualTo: name)
            query.getDocuments{ snapshot, error in
                guard let documents = snapshot?.documents else{
                    print("Error fetching documents: \(error?.localizedDescription ?? "Unknown error")")
                    return
                }
                for document in documents {
                    collectionRef.document(document.documentID).delete { error in
                        if let error = error {
                            print("Error deleting document: \(error.localizedDescription)")
                        } else {
                            print("Favorite successfully deleted!")
                        }
                    }
                }
            }
        }
    }
}

struct Drink: Codable, Identifiable{ // Codable能夠將JSON檔轉換成我們所定義的架構
    var name: String
    var description: String
    var Mprice: Int
    var Lprice: Int
    var hasHot: Bool = true
    var isFavorite: Bool = false
    var type: String
    @DocumentID var id: String? // 為了讓資料有識別的id & 遵從protocol Identifiable
    
    var size: String = "M"
    var ice: String = "正常冰"
    var sugar: String = "正常糖"
    var price: Int = 0
}

struct Favorite: Codable, Identifiable{
    var name: String
    @DocumentID var id: String?
}
